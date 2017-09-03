#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeGoto.generated.h"


UCLASS()
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeGoto : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	int32 GotoID;

	UPROPERTY(VisibleAnywhere)
	UDemoDialogueNode* Goto;
};
