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
    bool ValidateReply(int32 ReplyIndex);

protected:

	void Finalize();
	void PlayNode(class UDemoDialogueNode* InNextNode);

    bool CheckNodeConditions(class UDemoDialogueNode* Node) const;
    void TriggerNodeActions(class UDemoDialogueNode* Node, bool bNodeStart);

public:

    UPROPERTY(Transient)
    class UDemoDialogue* Dialogue;

    UPROPERTY(Transient)
    TArray<class ADemoBaseCharacter*> Actors;

protected:

	UPROPERTY(Transient)
	class UDemoDialogueNode* CurrentNode;

	UPROPERTY(Transient)
    bool bWaitingDelay;

    UPROPERTY(Transient)
    float DelayNextNode;

	UPROPERTY(Transient)
	bool bFinished;
};
