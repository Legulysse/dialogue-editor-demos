#include "Assets/Actions/DemoNodeAction.h"


UDemoNodeAction::UDemoNodeAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
    , bOnNodeStart(true)
{
}

void UDemoNodeAction::Execute(FDemoNodeContextAction& InContext)
{
}
