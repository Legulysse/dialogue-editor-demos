#pragma once

#include "UnrealEd.h"
#include "DemoDialogueFactory.generated.h"


UCLASS()
class UDemoDialogueFactory : public UFactory, public FReimportHandler
{
	GENERATED_UCLASS_BODY()

	void LoadFromText(class UDemoDialogue* InDialogue, const FString& JSonContent);

	// UFactory interface
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	virtual bool DoesSupportClass(UClass * Class) override;

	// FReimportHandler interface (check UReimportFbxStaticMeshFactory)
	virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;
	virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;
	virtual EReimportResult::Type Reimport(UObject* Obj) override;

protected:

    void ParseGroupConditions(const TSharedPtr<FJsonObject> JSonConditionGroup, class UDemoNodeConditionGroup* NewConditionGroup);
    class UDemoNodeCondition* ParseCondition(const TSharedPtr<FJsonObject> JSonCondition, UObject* Outer);
};
