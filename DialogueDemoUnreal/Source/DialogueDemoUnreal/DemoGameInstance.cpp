#include "DemoGameInstance.h"

#include "Dialogue/DemoDialogueManager.h"


UDemoGameInstance::UDemoGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DialogueManager = CreateDefaultSubobject<UDemoDialogueManager>("DialogueManager");
}
