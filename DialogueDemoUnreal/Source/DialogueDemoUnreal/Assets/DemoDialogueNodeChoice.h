#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeChoice.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeChoice : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	TArray< int32 > RepliesIDs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TArray< class UDemoDialogueNodeReply* > Replies;
};
