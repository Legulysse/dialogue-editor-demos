// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Characters/DemoAICharacter.h"

#include "Interactions/DemoInteractionComponent.h"

#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// ADemoAICharacter

ADemoAICharacter::ADemoAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InteractionComp = CreateDefaultSubobject<UDemoInteractionComponent>(TEXT("Interaction"));
	InteractionComp->SetupAttachment(RootComponent);
}

FRotator ADemoAICharacter::GetLookAtDirection() const
{
	FRotator LookAtDirection = Super::GetLookAtDirection();

	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetOuter(), 0);
	if (PlayerCharacter)
	{
		LookAtDirection = (PlayerCharacter->GetActorLocation() - GetActorLocation()).Rotation();
	}

	return LookAtDirection;
}
