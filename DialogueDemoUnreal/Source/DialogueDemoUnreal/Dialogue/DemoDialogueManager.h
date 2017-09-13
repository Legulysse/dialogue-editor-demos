#pragma once

#include "Tickable.h"
#include "Dialogue/DemoDialogueInstance.h"
#include "DemoDialogueManager.generated.h"


UCLASS(BlueprintType)
class UDemoDialogueManager : public UObject, public FTickableGameObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	bool PlayDialogue(const FDemoDialogueParams& Params);

protected:

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;

protected:

    UPROPERTY()
    TArray<UDemoDialogueInstance*> DialogueInstances;
};
