#pragma once

#include "DemoNodeConditionGroup.h"
#include "DemoNodeConditionGroupAnd.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoNodeConditionGroupAnd : public UDemoNodeConditionGroup
{
	GENERATED_UCLASS_BODY()

public:

    virtual bool IsValid(FDemoNodeContextCondition& InContext) const override;
};
