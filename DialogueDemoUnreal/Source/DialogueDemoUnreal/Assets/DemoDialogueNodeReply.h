#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeReply.generated.h"


UCLASS()
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeReply : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	FString Reply;
};
