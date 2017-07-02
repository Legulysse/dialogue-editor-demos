#include "DemoGameInstance.h"

#include "Dialogue/DemoDialogueManager.h"


UDemoGameInstance::UDemoGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//DialogueManager = CreateDefaultSubobject<UDemoDialogueManager>("DialogueManager");
}

void UDemoGameInstance::Init()
{
    DialogueManager = NewObject<UDemoDialogueManager>(Cast<UObject>(GetWorld()), "DialogueManager");
}

void UDemoGameInstance::Shutdown()
{
    DialogueManager = nullptr;
}
