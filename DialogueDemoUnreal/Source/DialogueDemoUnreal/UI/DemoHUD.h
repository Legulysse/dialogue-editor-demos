#pragma once

#include "Blueprint/UserWidget.h"
#include "DemoHUD.generated.h"


UCLASS(BlueprintType)
class UDemoHUD : public UUserWidget
{
    GENERATED_UCLASS_BODY()

public:

    void DisplayDialogueSentence();
    void HideDialogueSentence();

protected:

    UFUNCTION(BlueprintImplementableEvent)
    void OnDisplayDialogueSentence();

    UFUNCTION(BlueprintImplementableEvent)
    void OnHideDialogueSentence();
};
