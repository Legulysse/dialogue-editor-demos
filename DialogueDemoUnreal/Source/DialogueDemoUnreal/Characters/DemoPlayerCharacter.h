// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DemoBaseCharacter.h"
#include "DemoPlayerCharacter.generated.h"

UCLASS(config=Game)
class ADemoPlayerCharacter : public ADemoBaseCharacter
{
	GENERATED_UCLASS_BODY()

public:

    virtual void OnDialogueStarted(class UDemoDialogueInstance* DialogueInstance, bool bLock) override;
    virtual void OnDialogueFinished(class UDemoDialogueInstance* DialogueInstance) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	void UpdateInteractions();
	void UpdateHUD();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHUD_Impl();

	void OnInteract();
	void OnDialogueSkip();

    template<int32 ReplyIndex>
	void OnDialogueReply() { OnDialogueReply(ReplyIndex); }
	void OnDialogueReply(int32 ReplyIndex);

	// APawn interface
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

public:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDemoInteractionComponent* NearestInteraction;
};
