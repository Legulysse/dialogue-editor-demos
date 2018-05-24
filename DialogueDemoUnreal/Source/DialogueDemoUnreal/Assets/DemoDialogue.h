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

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString Version;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    EDemoDialogueSceneType SceneType;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    FString VoiceBank;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    int32 RootNodeID;

    UPROPERTY(VisibleAnywhere, Category="Dialogue")
    class UDemoDialogueNode* RootNode;

    UPROPERTY(VisibleAnywhere, Instanced, Category="Dialogue")
    TArray< class UDemoDialogueNode* > ListNodes;

#if WITH_EDITORONLY_DATA

    UPROPERTY(VisibleAnywhere, meta = (RelativeToGameContentDir), Category="Dialogue")
    FDirectoryPath ImportPath;

#endif // WITH_EDITORONLY_DATA

public:

    class UDemoDialogueNode* GetNodeByID(int32 ID) const;
};
