#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeBranch.generated.h"


UCLASS()
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeBranch : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	int32 BranchID;

	UPROPERTY(VisibleAnywhere)
    UDemoDialogueNode* Branch;
};
