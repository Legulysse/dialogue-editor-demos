#pragma once

#include "DemoNodeCondition.generated.h"


USTRUCT(BlueprintType)
struct FDemoNodeContextCondition
{
	GENERATED_BODY()

    const class UDemoDialogueInstance* DialogueInstance;
    const class UDemoDialogue* Dialogue;
    const class UDemoDialogueNode* Node;
};

UCLASS(BlueprintType, Abstract)
class DIALOGUEDEMOUNREAL_API UDemoNodeCondition : public UObject
{
	GENERATED_UCLASS_BODY()

public:

    virtual bool IsValid(FDemoNodeContextCondition& InContext) const;

public:

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    bool bIntendedResult;
};
