#pragma once

#include "DemoNodeConditionGroup.h"
#include "DemoNodeConditionGroupOr.generated.h"


UCLASS()
class DIALOGUEDEMOUNREAL_API UDemoNodeConditionGroupOr : public UDemoNodeConditionGroup
{
	GENERATED_UCLASS_BODY()

public:

    virtual bool IsValid(FDemoNodeContextCondition& InContext) const override;
};
