#pragma once

#include "DemoDialogueInstance.generated.h"


UCLASS(BlueprintType)
class UDemoDialogueInstance : public UObject
{
	GENERATED_UCLASS_BODY()

public:

    void Start();
    void Finalize();

    bool IsFinished() const;

    void Tick(float DeltaTime);

public:

    UPROPERTY()
    class UDemoDialogue* Dialogue;

    UPROPERTY()
    TArray<class ADemoBaseCharacter*> Actors;

    UPROPERTY()
    float Lifetime;

    UPROPERTY()
    bool bFinished;
};
