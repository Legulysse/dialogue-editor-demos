#pragma once

#include "Dialogue/DemoDialoguePrefab.h"
#include "DemoDialogueInstance.generated.h"


USTRUCT()
struct FDemoDialogueParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	class UDemoDialogue* Dialogue;

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	TArray<class ADemoBaseCharacter*> Actors;

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<class ADemoDialoguePrefab> PrefabClass;

	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	class AActor* Stagemark;
};

USTRUCT()
struct FDemoDialogueRole
{
    GENERATED_BODY()

    UPROPERTY(Transient)
    FString ID;

    UPROPERTY(Transient)
    class ADemoBaseCharacter* Actor;

    UPROPERTY(Transient)
    EDemoDialoguePrefabPosition PrefabPosition;
};

UCLASS(BlueprintType)
class UDemoDialogueInstance : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	bool InitDialogue(const FDemoDialogueParams& Params);
	void Start();
	void Stop();

    bool IsFinished() const;

    void Tick(float DeltaTime);

	void PlayNextNode();
    bool ValidateReply(int32 ReplyIndex);
	void SkipCurrentNode();

protected:

	void Finalize();
	void PlayNode(class UDemoDialogueNode* InNextNode);

    bool CheckNodeConditions(class UDemoDialogueNode* Node) const;
    void TriggerNodeActions(class UDemoDialogueNode* Node, bool bNodeStart);

	const FDemoDialogueRole* GetRole(FString ID);
	const FDemoDialogueRole* GetRoleFromPosition(EDemoDialoguePrefabPosition Position);

	void SelectCamera(const FString& SpeakerID);

protected:

    UPROPERTY(Transient)
    class UDemoDialogue* Dialogue;

    UPROPERTY(Transient)
	TArray<FDemoDialogueRole> Roles;

	UPROPERTY(Transient)
	class ADemoDialoguePrefab* Prefab;

	UPROPERTY(Transient)
	bool bUseCameras;

protected:

	UPROPERTY(Transient)
	class UDemoDialogueNode* CurrentNode;

	UPROPERTY(Transient)
    bool bWaitingDelay;

    UPROPERTY(Transient)
    float DelayNextNode;

	UPROPERTY(Transient)
	bool bFinished;
};
