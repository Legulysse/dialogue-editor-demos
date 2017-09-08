#pragma once

#include "DemoDialogueNode.h"
#include "DemoDialogueNodeSentence.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogueNodeSentence : public UDemoDialogueNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	FString Sentence;

    UPROPERTY(VisibleAnywhere)
    FString SpeakerID;

    UPROPERTY(VisibleAnywhere)
    FString ListenerID;

    UPROPERTY(VisibleAnywhere)
    FString VoicingID;

    UPROPERTY(VisibleAnywhere)
    bool bHideSubtitle;

    UPROPERTY(VisibleAnywhere)
    FString SpeakerAnimset;

    UPROPERTY(VisibleAnywhere)
    FString ListenerAnimset;

    UPROPERTY(VisibleAnywhere)
    FString SpeakerAnim;

    UPROPERTY(VisibleAnywhere)
    FString ListenerAnim;
};
