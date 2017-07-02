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

    virtual void Init() override;
    virtual void Shutdown() override;

public:

    UPROPERTY(BlueprintReadWrite, Category = DemoGameInstance)
    class UDemoHUD* HUD;

	UPROPERTY()
	class UDemoDialogueManager* DialogueManager;

	UPROPERTY()
	TArray<class UDemoInteractionComponent*> ListInteractibles;
};
