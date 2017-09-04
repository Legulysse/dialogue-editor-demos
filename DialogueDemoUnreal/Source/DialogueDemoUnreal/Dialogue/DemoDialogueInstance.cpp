#include "Dialogue/DemoDialogueInstance.h"

#include "Kismet/GameplayStatics.h"

#include "DemoGameInstance.h"
#include "Characters/DemoPlayerCharacter.h"
#include "UI/DemoHUD.h"


UDemoDialogueInstance::UDemoDialogueInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
    , Lifetime(0.f)
    , bFinished(false)
{
}

void UDemoDialogueInstance::InitDialogue(const FDemoDialogueParams& Params)
{
	Dialogue = Params.Dialogue;
	Actors = Params.Actors;
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
}

void UDemoDialogueInstance::Finalize()
{
    bFinished = true;

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
        Finalize();
    }
}
