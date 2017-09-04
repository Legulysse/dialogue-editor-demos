#include "Interactions/DemoInteractionComponent.h"

#include "Kismet/GameplayStatics.h"

#include "DemoGameInstance.h"
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

void UDemoInteractionComponent::PlayerInteract(ADemoPlayerCharacter* Player)
{
	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetOwner()));
	if (GameInstance)
	{
        FDemoDialogueParams Params;
        Params.Actors.Add(Player);
        Params.Actors.Add(Cast<ADemoBaseCharacter>(GetOwner()));
		GameInstance->DialogueManager->StartDialogue(Params);
	}
}
