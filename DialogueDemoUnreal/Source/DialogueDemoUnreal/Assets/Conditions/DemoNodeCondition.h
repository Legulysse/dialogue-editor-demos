#pragma once

#include "DemoNodeCondition.generated.h"


struct FDemoNodeContextCondition
{
public:

    const class UDemoDialogueInstance* DialogueInstance;
    const class UDemoDialogue* Dialogue;
    const class UDemoDialogueNode* Node;
};

UCLASS()
class DIALOGUEDEMOUNREAL_API UDemoNodeCondition : public UObject
{
	GENERATED_UCLASS_BODY()

public:

    virtual bool IsValid(FDemoNodeContextCondition& InContext) const;

public:

    UPROPERTY(VisibleAnywhere)
    bool bIntendedResult;
};
