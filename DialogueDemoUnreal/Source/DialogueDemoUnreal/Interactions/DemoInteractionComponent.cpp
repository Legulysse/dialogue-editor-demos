#include "Interactions/DemoInteractionComponent.h"

#include "Kismet/GameplayStatics.h"
#include "DemoGameInstance.h"


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

void UDemoInteractionComponent::Use()
{
}
