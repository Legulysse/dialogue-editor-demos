#include "Dialogue/DemoDialogueManager.h"

#include "Dialogue/DemoDialogueInstance.h"


UDemoDialogueManager::UDemoDialogueManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UDemoDialogueManager::StartDialogue(const FDialogueParams& Params)
{
    UDemoDialogueInstance* DialogueInstance = NewObject<UDemoDialogueInstance>(GetOuter());
    DialogueInstances.Add(DialogueInstance);

    DialogueInstance->Dialogue = Params.Dialogue;
    DialogueInstance->Actors = Params.Actors;
    DialogueInstance->Start();
	return true;
}

void UDemoDialogueManager::Tick(float DeltaTime)
{
    for (UDemoDialogueInstance* DialogueInstance : DialogueInstances)
    {
        if (!DialogueInstance->IsFinished())
            DialogueInstance->Tick(DeltaTime);
    }

    DialogueInstances.RemoveAll([](UDemoDialogueInstance* DialogueInstance) { return DialogueInstance->IsFinished(); });
}

bool UDemoDialogueManager::IsTickable() const
{
    return !IsTemplate();
}

TStatId UDemoDialogueManager::GetStatId() const
{
    return GetStatID();
}
