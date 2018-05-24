#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeBranch.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeBranch : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	int32 BranchID;

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
    UDemoDialogueNode* Branch;
};
