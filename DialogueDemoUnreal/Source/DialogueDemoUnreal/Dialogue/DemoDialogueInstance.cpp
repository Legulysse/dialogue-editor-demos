#include "Dialogue/DemoDialogueInstance.h"

#include "Kismet/GameplayStatics.h"

#include "DemoGameInstance.h"
#include "Assets/DemoDialogue.h"
#include "Assets/DemoDialogueNode.h"
#include "Assets/DemoDialogueNodeRoot.h"
#include "Characters/DemoPlayerCharacter.h"
#include "UI/DemoHUD.h"


UDemoDialogueInstance::UDemoDialogueInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
    , Lifetime(0.f)
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

    UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOuter()));
    if (GameInstance)
    {
		FDemoSentenceParams Params;
		Params.SpeakerName = "Ominous Voice";
		Params.SentenceText = "Hey, have you seen some Squarrels around here ?";
        GameInstance->HUD->DisplayDialogueSentence(Params);
    }

	if (Dialogue->RootNode && Dialogue->RootNode->IsA(UDemoDialogueNodeRoot::StaticClass()))
	{
		UDemoDialogueNodeRoot* Root = Cast<UDemoDialogueNodeRoot>(Dialogue->RootNode);

		CurrentNode = Root;

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

    Lifetime += DeltaTime;

    if (Lifetime >= 4.f)
    {
		Stop();
    }
}

void UDemoDialogueInstance::PlayNextNode()
{
	if (!CurrentNode)
		return;

	PlayNextNode(CurrentNode->Next);
}

void UDemoDialogueInstance::PlayNextNode(UDemoDialogueNode* InNextNode)
{
}
