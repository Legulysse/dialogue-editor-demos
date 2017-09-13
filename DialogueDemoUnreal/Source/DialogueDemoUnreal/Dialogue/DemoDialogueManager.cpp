#include "Dialogue/DemoDialogueManager.h"

#include "Dialogue/DemoDialogueInstance.h"
#include "Characters/DemoBaseCharacter.h"


UDemoDialogueManager::UDemoDialogueManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UDemoDialogueManager::PlayDialogue(const FDemoDialogueParams& Params)
{
	for (ADemoBaseCharacter* Actor : Params.Actors)
	{
		if (Actor->IsInDialogue())
			return false;
	}

    UDemoDialogueInstance* DialogueInstance = NewObject<UDemoDialogueInstance>(GetOuter());
	if (!DialogueInstance->InitDialogue(Params))
	{
		return false;
	}

	DialogueInstances.Add(DialogueInstance);
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
