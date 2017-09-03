#include "Assets/Conditions/DemoNodeConditionGroupOr.h"


UDemoNodeConditionGroupOr::UDemoNodeConditionGroupOr(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UDemoNodeConditionGroupOr::IsValid(FDemoNodeContextCondition& InContext) const
{
    if (Conditions.Num() == 0)
        return true;

    bool bValidConditions = false;
    for (UDemoNodeCondition* Condition : Conditions)
    {
        if (Condition->IsValid(InContext) == Condition->bIntendedResult)
        {
            bValidConditions = true;
            break;
        }
    }

    return bValidConditions;
}
