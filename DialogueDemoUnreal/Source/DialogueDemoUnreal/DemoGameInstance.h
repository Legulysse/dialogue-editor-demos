#pragma once

#include "Engine/GameInstance.h" 
#include "DemoGameInstance.generated.h"

//--------------------------------------------------------------
// GameInstanceClass is defined in DefaultEngine.ini
//

UCLASS()
class UDemoGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY()
	class UDemoDialogueManager* DialogueManager;

	UPROPERTY()
	TArray<class UDemoInteractionComponent*> ListInteractibles;
};
