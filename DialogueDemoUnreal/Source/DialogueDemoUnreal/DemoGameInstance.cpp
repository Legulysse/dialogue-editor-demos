#include "DemoGameInstance.h"

#include "Engine/World.h"

#include "Dialogue/DemoDialogueManager.h"


UDemoGameInstance::UDemoGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDemoGameInstance::Init()
{
    DialogueManager = NewObject<UDemoDialogueManager>(GetWorld(), "DialogueManager");
}

void UDemoGameInstance::Shutdown()
{
    DialogueManager = nullptr;
}
