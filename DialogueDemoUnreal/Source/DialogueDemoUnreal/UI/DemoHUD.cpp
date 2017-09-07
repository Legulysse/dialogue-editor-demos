#include "UI/DemoHUD.h"


UDemoHUD::UDemoHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UDemoHUD::DisplayDialogueSentence(const FDemoSentenceParams& Params)
{
	ReceiveDisplayDialogueSentence(Params);
}

void UDemoHUD::HideDialogueSentence()
{
    ReceiveHideDialogueSentence();
}

void UDemoHUD::DisplayDialogueChoice(const FDemoChoiceParams& Params)
{
	ReceiveDisplayDialogueChoice(Params);
}

void UDemoHUD::HideDialogueChoice()
{
	ReceiveHideDialogueChoice();
}
