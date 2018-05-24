#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeGoto.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeGoto : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	int32 GotoID;

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	UDemoDialogueNode* Goto;
};
