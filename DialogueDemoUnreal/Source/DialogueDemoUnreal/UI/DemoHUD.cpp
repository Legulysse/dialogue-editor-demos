#include "UI/DemoHUD.h"


UDemoHUD::UDemoHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UDemoHUD::DisplayDialogueSentence(const FDemoSentenceParams& Params)
{
    OnDisplayDialogueSentence(Params);
}

void UDemoHUD::HideDialogueSentence()
{
    OnHideDialogueSentence();
}
