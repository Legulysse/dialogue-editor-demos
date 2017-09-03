// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Characters/DemoPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Interactions/DemoInteractionComponent.h"
#include "DemoGameInstance.h"


//////////////////////////////////////////////////////////////////////////
// ADemoPlayerCharacter

ADemoPlayerCharacter::ADemoPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ADemoPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateInteractions();
	UpdateHUD();
}

void ADemoPlayerCharacter::UpdateInteractions()
{
	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(this));

	NearestInteraction = nullptr;

    if (IsInDialogue())
        return;

	for (UDemoInteractionComponent* Interaction : GameInstance->ListInteractibles)
	{
		if (Interaction->IsOverlappingActor(this))
		{
			NearestInteraction = Interaction;
		}
	}
}

void ADemoPlayerCharacter::UpdateHUD()
{
	UpdateHUD_Impl();
}

void ADemoPlayerCharacter::OnInteract()
{
	if (NearestInteraction)
	{
		NearestInteraction->PlayerInteract(this);

		NearestInteraction = nullptr;
	}
}

void ADemoPlayerCharacter::OnDialogueStarted(class UDemoDialogueInstance* DialogueInstance)
{
    Super::OnDialogueStarted(DialogueInstance);
}

void ADemoPlayerCharacter::OnDialogueFinished(class UDemoDialogueInstance* DialogueInstance)
{
    Super::OnDialogueFinished(DialogueInstance);
}

void ADemoPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADemoPlayerCharacter::OnInteract);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADemoPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADemoPlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADemoPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADemoPlayerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADemoPlayerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADemoPlayerCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADemoPlayerCharacter::OnResetVR);
}