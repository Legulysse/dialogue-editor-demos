#include "UI/DemoHUD.h"


UDemoHUD::UDemoHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UDemoHUD::DisplayDialogueSentence()
{
    OnDisplayDialogueSentence();
}

void UDemoHUD::HideDialogueSentence()
{
    OnHideDialogueSentence();
}
