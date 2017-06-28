// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DialogueDemoUnrealGameMode.h"
#include "UObject/ConstructorHelpers.h"

ADialogueDemoUnrealGameMode::ADialogueDemoUnrealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DialogueDemo/Demo_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
