#include "Assets/Conditions/DemoNodeConditionGroup.h"


UDemoNodeConditionGroup::UDemoNodeConditionGroup(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UDemoNodeConditionGroup::IsValid(FDemoNodeContextCondition& InContext) const
{
    return false;
}
