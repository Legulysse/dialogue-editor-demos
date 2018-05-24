#pragma once

#include "DemoDialogueNode.generated.h"


UCLASS(BlueprintType, Abstract)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNode : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	int32 ID;

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	int32 NextID;

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
    UDemoDialogueNode* Next;

    UPROPERTY(VisibleAnywhere, Instanced, Category="Dialogue")
    TArray< class UDemoNodeCondition* > Conditions;

    UPROPERTY(VisibleAnywhere, Instanced, Category="Dialogue")
    TArray< class UDemoNodeAction* > Actions;

    UPROPERTY(VisibleAnywhere, Instanced, Category="Dialogue")
    TArray< class UDemoNodeFlag* > Flags;
};
