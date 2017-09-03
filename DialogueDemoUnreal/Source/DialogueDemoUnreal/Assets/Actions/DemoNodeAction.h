#pragma once

#include "DemoNodeAction.generated.h"


struct FDemoNodeContextAction
{
public:

    class UDemoDialogueInstance* DialogueInstance;
    class UDemoDialogue* Dialogue;
    class UDemoDialogueNode* Node;
};

UCLASS()
class DIALOGUEDEMOUNREAL_API UDemoNodeAction : public UObject
{
	GENERATED_UCLASS_BODY()

public:

    virtual void Execute(FDemoNodeContextAction& InContext);

public:

    UPROPERTY(VisibleAnywhere)
    bool bOnNodeStart;
};
