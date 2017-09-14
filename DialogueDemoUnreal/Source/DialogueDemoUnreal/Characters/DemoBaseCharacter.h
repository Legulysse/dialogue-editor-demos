// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoBaseCharacter.generated.h"

UCLASS(config=Game)
class ADemoBaseCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	bool PlayDialogue(class UDemoDialogue* Dialogue);

    virtual void OnDialogueStarted(class UDemoDialogueInstance* DialogueInstance);
    virtual void OnDialogueFinished(class UDemoDialogueInstance* DialogueInstance);

	UFUNCTION(BlueprintPure, Category = Dialogue)
    bool IsInDialogue() const;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DemoCharacter)
	TSubclassOf<class UDemoCharacterSheet> CharacterSheet;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DemoCharacter)
    class UDemoDialogueInstance* CurrentDialogueInstance;
};
