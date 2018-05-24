#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeSentence.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeSentence : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category="Dialogue")
	FString Sentence;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString SpeakerID;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString ListenerID;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString VoicingID;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    bool bHideSubtitle;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString SpeakerAnimset;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString ListenerAnimset;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString SpeakerAnim;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString ListenerAnim;
};
