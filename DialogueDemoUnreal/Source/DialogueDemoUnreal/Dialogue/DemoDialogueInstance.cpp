#include "Dialogue/DemoDialogueInstance.h"

#include "Kismet/GameplayStatics.h"

#include "DemoGameInstance.h"
#include "Assets/DemoDialogue.h"
#include "Assets/DemoDialogueNode.h"
#include "Assets/DemoDialogueNodeBranch.h"
#include "Assets/DemoDialogueNodeChoice.h"
#include "Assets/DemoDialogueNodeGoto.h"
#include "Assets/DemoDialogueNodeReply.h"
#include "Assets/DemoDialogueNodeRoot.h"
#include "Assets/DemoDialogueNodeSentence.h"
#include "Assets/Actions/DemoNodeAction.h"
#include "Assets/Conditions/DemoNodeCondition.h"
#include "Assets/Flags/DemoNodeFlag.h"
#include "Characters/DemoPlayerCharacter.h"
#include "Characters/DemoCharacterSheet.h"
#include "Dialogue/DemoDialogueCamera.h"
#include "Dialogue/DemoDialoguePrefab.h"
#include "UI/DemoHUD.h"


UDemoDialogueInstance::UDemoDialogueInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bUseCameras(false)
    , bWaitingDelay(false)
    , DelayNextNode(0.f)
    , bFinished(false)
{
}

bool UDemoDialogueInstance::InitDialogue(const FDemoDialogueParams& Params)
{
	if (!Params.Dialogue)
		return false;

	Dialogue = Params.Dialogue;

    // Setup Roles and Characters
    int32 IndexPrefabPosition = 0;
    for (auto Actor : Params.Actors)
    {
        FDemoDialogueRole Role;
        Role.Actor = Actor;
        Role.PrefabPosition = (EDemoDialoguePrefabPosition)IndexPrefabPosition++;
        if (Role.Actor && Role.Actor->CharacterSheet)
        {
            Role.ID = Role.Actor->CharacterSheet.GetDefaultObject()->ID;
        }
        Roles.Add(Role);
    }

    // Setup Prefab
	UWorld* World = GetOuter()->GetWorld();
	if (Params.PrefabClass && Params.Stagemark && World)
	{
		FTransform Transform = Params.Stagemark->GetTransform();
		FActorSpawnParameters PrefabSpawnParams;
		Prefab = Cast<ADemoDialoguePrefab>(World->SpawnActor(Params.PrefabClass, &Transform, PrefabSpawnParams));

		// Place characters on their position
		if (Prefab)
		{
			bUseCameras = true;

			TSet<UActorComponent*> Components = Prefab->GetComponents();
			for (auto Component : Components)
			{
				UDemoDialoguePrefabRolePosition* RolePositionComponent = Cast<UDemoDialoguePrefabRolePosition>(Component);
				if (RolePositionComponent)
				{
					const FDemoDialogueRole* Role = GetRoleFromPosition(RolePositionComponent->Position);
					if (Role && Role->Actor)
					{
						Role->Actor->TeleportTo(FVector(0, 0, Role->Actor->GetDefaultHalfHeight()) + RolePositionComponent->GetComponentLocation(), RolePositionComponent->GetComponentRotation(), false, true);
					}
				}
			}
		}
	}

	return true;
}

void UDemoDialogueInstance::Start()
{
	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetOuter(), 0);

	bool bLockCharacters = bUseCameras;
    for (const auto& Role : Roles)
    {
        Role.Actor->OnDialogueStarted(this, bLockCharacters);
    }

	if (Dialogue->RootNode && Dialogue->RootNode->IsA(UDemoDialogueNodeRoot::StaticClass()))
	{
		UDemoDialogueNodeRoot* Root = Cast<UDemoDialogueNodeRoot>(Dialogue->RootNode);

		CurrentNode = Root;
        TriggerNodeActions(CurrentNode, true);

		PlayNextNode();
	}
	else
	{
		Stop();
	}
}

void UDemoDialogueInstance::Stop()
{
	bFinished = true;

	Finalize();
}

void UDemoDialogueInstance::Finalize()
{
    UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOuter()));
    if (GameInstance)
    {
        GameInstance->HUD->HideDialogueSentence();
	}

    for (const auto& Role : Roles)
	{
		Role.Actor->OnDialogueFinished(this);
	}

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetOuter(), 0);
	if (Controller && Prefab)
	{
		if (bUseCameras)
		{
			FViewTargetTransitionParams Params;
			Controller->SetViewTarget(Controller->GetPawn(), Params);
		}

		Prefab->Destroy();
		Prefab = nullptr;
	}
}

bool UDemoDialogueInstance::IsFinished() const
{
    return bFinished;
}

void UDemoDialogueInstance::Tick(float DeltaTime)
{
    if (IsFinished())
        return;

    if (bWaitingDelay)
    {
        DelayNextNode -= DeltaTime;

        if (DelayNextNode <= 0.f)
        {
            PlayNextNode();
        }
    }
}

void UDemoDialogueInstance::SkipCurrentNode()
{
	if (!CurrentNode)
		return;

	if (CurrentNode->IsA(UDemoDialogueNodeSentence::StaticClass()))
	{
		PlayNextNode();
	}
}

void UDemoDialogueInstance::PlayNextNode()
{
	if (!CurrentNode)
		return;

	PlayNode(CurrentNode->Next);
}

void UDemoDialogueInstance::PlayNode(UDemoDialogueNode* NextNode)
{
	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOuter()));
	if (!GameInstance)
	{
		Stop();
		return;
	}

    if (CurrentNode)
    {
        TriggerNodeActions(CurrentNode, false);

        CurrentNode = nullptr;
    }

    bWaitingDelay = false;
    DelayNextNode = 0.f;

    if (!NextNode)
    {
        Stop();
        return;
    }

    if (!NextNode->IsA(UDemoDialogueNodeReply::StaticClass()))
    {
        if (!CheckNodeConditions(NextNode))
        {
            PlayNode(NextNode->Next);
            return;
        }
    }

    CurrentNode = NextNode;

    if (CurrentNode->IsA(UDemoDialogueNodeSentence::StaticClass()))
    {
        UDemoDialogueNodeSentence* NodeSentence = Cast<UDemoDialogueNodeSentence>(CurrentNode);

        const FDemoDialogueRole* RoleSpeaker = GetRole(NodeSentence->SpeakerID);

		// Subtitle
		FDemoSentenceParams Params;
		Params.SpeakerName = NodeSentence->SpeakerID;
		Params.SentenceText = NodeSentence->Sentence;
		Params.NodeSentence = NodeSentence;

        if (RoleSpeaker && RoleSpeaker->Actor && RoleSpeaker->Actor->CharacterSheet)
        {
            Params.SpeakerName = RoleSpeaker->Actor->CharacterSheet.GetDefaultObject()->DisplayName;
        }

		GameInstance->HUD->DisplayDialogueSentence(Params);

		// Animation
		// TODO: Get characters from their ID
		//if (SpeakerCharacter && ListenerCharacter)
		//{
		//	FRotator RotationSpeakerToListener = (ListenerCharacter->GetActorLocation() - SpeakerCharacter->GetActorLocation()).Rotation();
		//	RotationSpeakerToListener.Pitch = 0;
		//	SpeakerCharacter->SetActorRotation(RotationSpeakerToListener);
		//}

		// Camera
		SelectCamera(NodeSentence->SpeakerID, NodeSentence->ListenerID);

        bWaitingDelay = true;
        DelayNextNode = 3.f;
    }

    TriggerNodeActions(CurrentNode, true);

    if (CurrentNode->IsA(UDemoDialogueNodeChoice::StaticClass()))
    {
        UDemoDialogueNodeChoice* NodeChoice = Cast<UDemoDialogueNodeChoice>(CurrentNode);

        // TODO: Handle conditions on Replies

		FDemoChoiceParams Params;
		Params.NodeChoice = NodeChoice;
		GameInstance->HUD->DisplayDialogueChoice(Params);
    }
    else if (CurrentNode->IsA(UDemoDialogueNodeReply::StaticClass()))
    {
        UDemoDialogueNodeReply* NodeReply = Cast<UDemoDialogueNodeReply>(CurrentNode);
        PlayNode(NodeReply->Next);
    }
    else if (CurrentNode->IsA(UDemoDialogueNodeGoto::StaticClass()))
    {
        UDemoDialogueNodeGoto* NodeGoto = Cast<UDemoDialogueNodeGoto>(CurrentNode);
        PlayNode(NodeGoto->Goto);
    }
    else if (CurrentNode->IsA(UDemoDialogueNodeBranch::StaticClass()))
    {
        UDemoDialogueNodeBranch* NodeBranch = Cast<UDemoDialogueNodeBranch>(CurrentNode);
        PlayNode(NodeBranch->Branch);
    }
}

bool UDemoDialogueInstance::ValidateReply(int32 ReplyIndex)
{
    UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOuter()));

    UDemoDialogueNodeChoice* NodeChoice = Cast<UDemoDialogueNodeChoice>(CurrentNode);
    if (!NodeChoice)
        return false;

    if (ReplyIndex < 0 || ReplyIndex >= NodeChoice->Replies.Num())
        return false;

    GameInstance->HUD->ValidateDialogueReply(ReplyIndex);

    PlayNode(NodeChoice->Replies[ReplyIndex]);
    return true;
}

bool UDemoDialogueInstance::CheckNodeConditions(UDemoDialogueNode* Node) const
{
    FDemoNodeContextCondition NodeContext;
    NodeContext.DialogueInstance = this;
    NodeContext.Dialogue = Dialogue;
    NodeContext.Node = Node;

    bool bValidConditions = true;
    for (UDemoNodeCondition* Condition : Node->Conditions)
    {
        if (Condition->IsValid(NodeContext) != Condition->bIntendedResult)
        {
            bValidConditions = false;
            break;
        }
    }

    return bValidConditions;
}

void UDemoDialogueInstance::TriggerNodeActions(UDemoDialogueNode* Node, bool bNodeStart)
{
    if (!Node)
        return;

    FDemoNodeContextAction NodeContext;
    NodeContext.DialogueInstance = this;
    NodeContext.Dialogue = Dialogue;
    NodeContext.Node = Node;

    for (UDemoNodeAction* Action : Node->Actions)
    {
        if (Action->bOnNodeStart == bNodeStart)
            Action->Execute(NodeContext);
    }
}

const FDemoDialogueRole* UDemoDialogueInstance::GetRole(FString ID)
{
    for (const auto& Role : Roles)
    {
        if (Role.ID == ID)
        {
            return &Role;
        }
    }
    return nullptr;
}

const FDemoDialogueRole* UDemoDialogueInstance::GetRoleFromPosition(EDemoDialoguePrefabPosition Position)
{
	for (const auto& Role : Roles)
	{
		if (Role.PrefabPosition == Position)
		{
			return &Role;
		}
	}
	return nullptr;
}

void UDemoDialogueInstance::SelectCamera(const FString& SpeakerID, const FString& ListenerID)
{
	if (!Prefab || !bUseCameras)
		return;

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetOuter(), 0);
	if (!Controller)
		return;

    EDemoDialoguePrefabPosition SpeakerPosition = EDemoDialoguePrefabPosition::Character_01;
    if (const FDemoDialogueRole* Role = GetRole(SpeakerID))
    {
        SpeakerPosition = Role->PrefabPosition;
    }

	EDemoDialoguePrefabPosition ListenerPosition = EDemoDialoguePrefabPosition::Character_02;
	if (const FDemoDialogueRole* Role = GetRole(ListenerID))
	{
		ListenerPosition = Role->PrefabPosition;
	}

    TArray<ADemoDialogueCamera*> PreferredCameras;

	TSet<UActorComponent*> Components = Prefab->GetComponents();
	for (auto Component : Components)
	{
		UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(Component);
		if (ChildActorComponent)
		{
			ADemoDialogueCamera* Camera = Cast<ADemoDialogueCamera>(ChildActorComponent->GetChildActor());
			if (Camera && Camera->Speaker == SpeakerPosition && Camera->Listener == ListenerPosition)
			{
                PreferredCameras.AddUnique(Camera);
			}
		}
	}

	if (PreferredCameras.Num() > 0)
	{
		FViewTargetTransitionParams Params;
		Controller->SetViewTarget(PreferredCameras[FMath::RandHelper(PreferredCameras.Num())], Params);
	}
}
