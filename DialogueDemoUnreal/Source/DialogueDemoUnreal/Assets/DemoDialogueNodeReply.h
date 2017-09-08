#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeReply.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeReply : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	FString Reply;
};
