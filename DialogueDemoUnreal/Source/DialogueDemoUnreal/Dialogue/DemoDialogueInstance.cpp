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
#include "UI/DemoHUD.h"


UDemoDialogueInstance::UDemoDialogueInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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
	Actors = Params.Actors;

	return true;
}

void UDemoDialogueInstance::Start()
{
    for (ADemoBaseCharacter* Actor : Actors)
    {
        Actor->OnDialogueStarted(this);
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

	for (ADemoBaseCharacter* Actor : Actors)
	{
		Actor->OnDialogueFinished(this);
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

		FDemoSentenceParams Params;
		Params.SpeakerName = NodeSentence->SpeakerID;
		Params.SentenceText = NodeSentence->Sentence;
		Params.NodeSentence = NodeSentence;
		GameInstance->HUD->DisplayDialogueSentence(Params);

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
