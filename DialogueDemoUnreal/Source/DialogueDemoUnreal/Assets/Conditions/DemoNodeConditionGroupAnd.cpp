#include "Assets/Conditions/DemoNodeConditionGroupAnd.h"


UDemoNodeConditionGroupAnd::UDemoNodeConditionGroupAnd(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UDemoNodeConditionGroupAnd::IsValid(FDemoNodeContextCondition& InContext) const
{
    if (Conditions.Num() == 0)
        return true;

    bool bValidConditions = true;
    for (UDemoNodeCondition* Condition : Conditions)
    {
        if (Condition->IsValid(InContext) != Condition->bIntendedResult)
        {
            bValidConditions = false;
            break;
        }
    }

    return bValidConditions;
}
