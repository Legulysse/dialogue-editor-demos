#pragma once

#include "Blueprint/UserWidget.h"
#include "DemoHUD.generated.h"


USTRUCT()
struct FDemoSentenceParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	FString SpeakerName = "Speaker Name";

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	FString SentenceText = "Sentence Text";
};

UCLASS(BlueprintType)
class UDemoHUD : public UUserWidget
{
    GENERATED_UCLASS_BODY()

public:

    void DisplayDialogueSentence(const FDemoSentenceParams& Params);
    void HideDialogueSentence();

protected:

    UFUNCTION(BlueprintImplementableEvent)
    void OnDisplayDialogueSentence(const FDemoSentenceParams& Params);

    UFUNCTION(BlueprintImplementableEvent)
    void OnHideDialogueSentence();
};
