#pragma once

#include "DemoDialogueInstance.generated.h"


USTRUCT()
struct FDemoDialogueParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	class UDemoDialogue* Dialogue;

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	TArray<class ADemoBaseCharacter*> Actors;
};

UCLASS(BlueprintType)
class UDemoDialogueInstance : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	void InitDialogue(const FDemoDialogueParams& Params);
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
