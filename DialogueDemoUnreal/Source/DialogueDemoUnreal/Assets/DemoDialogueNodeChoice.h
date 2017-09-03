#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeChoice.generated.h"


UCLASS()
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeChoice : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	TArray< int32 > RepliesIDs;

	UPROPERTY(VisibleAnywhere)
	TArray< class UDemoDialogueNodeReply* > Replies;
};
