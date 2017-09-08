#pragma once

#include "DemoDialogueNode.generated.h"


UCLASS(BlueprintType, Abstract)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNode : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	int32 ID;

	UPROPERTY(VisibleAnywhere)
	int32 NextID;

	UPROPERTY(VisibleAnywhere)
    UDemoDialogueNode* Next;

    UPROPERTY(VisibleAnywhere, Instanced)
    TArray< class UDemoNodeCondition* > Conditions;

    UPROPERTY(VisibleAnywhere, Instanced)
    TArray< class UDemoNodeAction* > Actions;

    UPROPERTY(VisibleAnywhere, Instanced)
    TArray< class UDemoNodeFlag* > Flags;
};
