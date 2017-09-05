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

	bool InitDialogue(const FDemoDialogueParams& Params);
	void Start();
	void Stop();

    bool IsFinished() const;

    void Tick(float DeltaTime);

	void PlayNextNode();

protected:

	void Finalize();
	void PlayNextNode(class UDemoDialogueNode* InNextNode);

public:

    UPROPERTY(Transient)
    class UDemoDialogue* Dialogue;

    UPROPERTY(Transient)
    TArray<class ADemoBaseCharacter*> Actors;

protected:

	UPROPERTY(Transient)
	class UDemoDialogueNode* CurrentNode;

	UPROPERTY(Transient)
	float Lifetime;

	UPROPERTY(Transient)
	bool bFinished;
};
