// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Characters/DemoBaseCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "DemoGameInstance.h"
#include "Dialogue/DemoDialogueManager.h"

//////////////////////////////////////////////////////////////////////////
// ADemoCharacter

ADemoBaseCharacter::ADemoBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	bLockForDialogue = false;
}

bool ADemoBaseCharacter::PlayDialogue(class UDemoDialogue* Dialogue)
{
	TArray<class ADemoBaseCharacter*> OtherActors;
	return PlayDialogueWithActors(Dialogue, OtherActors);
}

bool ADemoBaseCharacter::PlayDialogueWithActors(class UDemoDialogue* Dialogue, const TArray<class ADemoBaseCharacter*>& OtherActors)
{
	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance && GameInstance->DialogueManager)
	{
		FDemoDialogueParams Params;
		Params.Dialogue = Dialogue;
		Params.Actors.Add(this);
		Params.Actors.Append(OtherActors);
		return GameInstance->DialogueManager->PlayDialogue(Params);
	}

	return false;
}

void ADemoBaseCharacter::OnDialogueStarted(class UDemoDialogueInstance* DialogueInstance, bool bLock)
{
    CurrentDialogueInstance = DialogueInstance;
	bLockForDialogue = bLock;
}

void ADemoBaseCharacter::OnDialogueFinished(class UDemoDialogueInstance* DialogueInstance)
{
	CurrentDialogueInstance = nullptr;
	bLockForDialogue = false;
}

bool ADemoBaseCharacter::IsInDialogue() const
{
    return CurrentDialogueInstance != nullptr;
}

void ADemoBaseCharacter::TurnAtRate(float Rate)
{
	if (bLockForDialogue)
		return;

	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADemoBaseCharacter::LookUpAtRate(float Rate)
{
	if (bLockForDialogue)
		return;

	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADemoBaseCharacter::MoveForward(float Value)
{
	if (bLockForDialogue)
		return;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADemoBaseCharacter::MoveRight(float Value)
{
	if (bLockForDialogue)
		return;

	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
