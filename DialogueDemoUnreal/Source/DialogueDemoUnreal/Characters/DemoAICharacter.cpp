// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Characters/DemoAICharacter.h"

#include "Interactions/DemoInteractionComponent.h"


//////////////////////////////////////////////////////////////////////////
// ADemoAICharacter

ADemoAICharacter::ADemoAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InteractionComp = CreateDefaultSubobject<UDemoInteractionComponent>(TEXT("Interaction"));
	InteractionComp->SetupAttachment(RootComponent);
}
