// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DemoBaseCharacter.h"
#include "DemoAICharacter.generated.h"

UCLASS(config=Game)
class ADemoAICharacter : public ADemoBaseCharacter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AICharacter)
	class UDemoInteractionComponent* InteractionComp;
};
