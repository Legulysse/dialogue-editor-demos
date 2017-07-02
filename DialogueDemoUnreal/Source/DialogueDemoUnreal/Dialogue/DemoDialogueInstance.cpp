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

void UDemoDialogueInstance::Start()
{
    for (ADemoBaseCharacter* Actor : Actors)
    {
        Actor->OnDialogueStarted(this);
    }

    UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOuter()));
    if (GameInstance)
    {
        GameInstance->HUD->DisplayDialogueSentence();
    }
}

void UDemoDialogueInstance::Finalize()
{
    bFinished = true;

    for (ADemoBaseCharacter* Actor : Actors)
    {
        Actor->OnDialogueFinished(this);
    }

    UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOuter()));
    if (GameInstance)
    {
        GameInstance->HUD->HideDialogueSentence();
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

    if (Lifetime >= 5.f)
    {
        Finalize();
    }
}
