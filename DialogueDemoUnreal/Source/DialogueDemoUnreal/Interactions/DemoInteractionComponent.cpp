#include "Interactions/DemoInteractionComponent.h"

#include "Kismet/GameplayStatics.h"

#include "DemoGameInstance.h"
#include "Characters/DemoAICharacter.h"
#include "Characters/DemoPlayerCharacter.h"
#include "Dialogue/DemoDialogueManager.h"


UDemoInteractionComponent::UDemoInteractionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;
}

void UDemoInteractionComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOwner()));
	if (GameInstance)
	{
		GameInstance->ListInteractibles.AddUnique(this);
	}
}

bool UDemoInteractionComponent::CanPlayerInteract(ADemoPlayerCharacter* Player) const
{
	if (IsOverlappingActor(Player))
	{
		ADemoAICharacter* CharacterOwner = Cast<ADemoAICharacter>(GetOwner());
		if (CharacterOwner && CharacterOwner->Dialogue)
		{
			return true;
		}
	}

	return false;
}

void UDemoInteractionComponent::PlayerInteract(ADemoPlayerCharacter* Player)
{
	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOwner()));
	if (GameInstance)
	{
		ADemoAICharacter* CharacterOwner = Cast<ADemoAICharacter>(GetOwner());
		if (CharacterOwner && CharacterOwner->Dialogue)
		{
			FDemoDialogueParams Params;
			Params.Dialogue = CharacterOwner->Dialogue;
			Params.Actors.Add(Player);
			Params.Actors.Add(CharacterOwner);
			Params.PrefabClass = CharacterOwner->DialoguePrefabClass;
			Params.Stagemark = CharacterOwner->DialogueStagemark;
			GameInstance->DialogueManager->PlayDialogue(Params);
		}
	}
}
