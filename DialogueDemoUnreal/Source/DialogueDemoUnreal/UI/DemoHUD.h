#pragma once

#include "Blueprint/UserWidget.h"
#include "DemoHUD.generated.h"


USTRUCT(BlueprintType)
struct FDemoSentenceParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	FString SpeakerName = "Speaker Name";

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	FString SentenceText = "Sentence Text";

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	const class UDemoDialogueNodeSentence* NodeSentence;
};

USTRUCT(BlueprintType)
struct FDemoChoiceParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	const class UDemoDialogueNodeChoice* NodeChoice;
};

UCLASS(BlueprintType)
class UDemoHUD : public UUserWidget
{
    GENERATED_UCLASS_BODY()

public:

    void DisplayDialogueSentence(const FDemoSentenceParams& Params);
	void HideDialogueSentence();
	void DisplayDialogueChoice(const FDemoChoiceParams& Params);
	void HideDialogueChoice();
    void ValidateDialogueReply(int32 ReplyIndex);

protected:

    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveDisplayDialogueSentence(const FDemoSentenceParams& Params);

    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveHideDialogueSentence();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveDisplayDialogueChoice(const FDemoChoiceParams& Params);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveHideDialogueChoice();

    UFUNCTION(BlueprintImplementableEvent)
    void ReceiveValidateDialogueReply(int32 ReplyIndex);
};
