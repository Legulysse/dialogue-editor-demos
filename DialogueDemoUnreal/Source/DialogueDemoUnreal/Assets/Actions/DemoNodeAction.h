#pragma once

#include "DemoNodeAction.generated.h"


USTRUCT(BlueprintType)
struct FDemoNodeContextAction
{
	GENERATED_BODY()

    class UDemoDialogueInstance* DialogueInstance;
    class UDemoDialogue* Dialogue;
    class UDemoDialogueNode* Node;
};

UCLASS(BlueprintType, Abstract)
class DIALOGUEDEMOUNREAL_API UDemoNodeAction : public UObject
{
	GENERATED_UCLASS_BODY()

public:

    virtual void Execute(FDemoNodeContextAction& InContext);

public:

    UPROPERTY(VisibleAnywhere)
    bool bOnNodeStart;
};
