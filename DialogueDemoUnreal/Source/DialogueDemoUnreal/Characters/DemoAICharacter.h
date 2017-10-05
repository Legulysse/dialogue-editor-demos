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

	virtual FRotator GetLookAtDirection() const override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AICharacter)
	class UDemoInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AICharacter)
	class UDemoDialogue* Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AICharacter)
	TSubclassOf<class ADemoDialoguePrefab> DialoguePrefabClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AICharacter)
	class AActor* DialogueStagemark;
};
