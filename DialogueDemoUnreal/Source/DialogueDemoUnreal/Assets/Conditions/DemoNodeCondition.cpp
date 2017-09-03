#include "Assets/Conditions/DemoNodeCondition.h"


UDemoNodeCondition::UDemoNodeCondition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
    , bIntendedResult(true)
{
}

bool UDemoNodeCondition::IsValid(FDemoNodeContextCondition& InContext) const
{
    return false;
}
