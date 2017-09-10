#pragma once

#include "DemoDialogue.generated.h"


UENUM(BlueprintType)
enum class EDemoDialogueSceneType : uint8
{
    Interactive 	UMETA(DisplayName = "Interactive"),
    Cinematic 	    UMETA(DisplayName = "Cinematic"),
    Ambient	        UMETA(DisplayName = "Ambient"),
    Monologue	    UMETA(DisplayName = "Monologue")
};

UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogue : public UObject
{
	GENERATED_UCLASS_BODY()

public:

    UPROPERTY(VisibleAnywhere)
    FString Version;

    UPROPERTY(VisibleAnywhere)
    EDemoDialogueSceneType SceneType;

    UPROPERTY(VisibleAnywhere)
    FString VoiceBank;

    UPROPERTY(VisibleAnywhere)
    int32 RootNodeID;

    UPROPERTY(VisibleAnywhere)
    class UDemoDialogueNode* RootNode;

    UPROPERTY(VisibleAnywhere, Instanced)
    TArray< class UDemoDialogueNode* > ListNodes;

#if WITH_EDITORONLY_DATA

    UPROPERTY(VisibleAnywhere, meta = (RelativeToGameContentDir))
    FDirectoryPath ImportPath;

#endif // WITH_EDITORONLY_DATA

public:

    class UDemoDialogueNode* GetNodeByID(int32 ID) const;
};
