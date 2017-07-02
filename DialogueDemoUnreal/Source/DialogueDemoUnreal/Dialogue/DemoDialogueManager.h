#pragma once

#include "Tickable.h"
#include "DemoDialogueManager.generated.h"


USTRUCT()
struct FDialogueParams
{
    GENERATED_BODY()

    UPROPERTY()
    class UDemoDialogue* Dialogue;

    UPROPERTY()
    TArray<class ADemoBaseCharacter*> Actors;
};

UCLASS(BlueprintType)
class UDemoDialogueManager : public UObject, public FTickableGameObject
{
	GENERATED_UCLASS_BODY()

public:

	bool StartDialogue(const FDialogueParams& Params);

protected:

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;

protected:

    UPROPERTY()
    TArray<class UDemoDialogueInstance*> DialogueInstances;
};
