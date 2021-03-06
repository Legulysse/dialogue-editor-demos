#include "DemoGameInstance.h"

#include "Engine/World.h"

#include "Dialogue/DemoDialogueManager.h"


UDemoGameInstance::UDemoGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDemoGameInstance::Init()
{
	Super::Init();

    DialogueManager = NewObject<UDemoDialogueManager>(this, "DialogueManager");
}

void UDemoGameInstance::Shutdown()
{
    DialogueManager = nullptr;

	Super::Shutdown();
}
