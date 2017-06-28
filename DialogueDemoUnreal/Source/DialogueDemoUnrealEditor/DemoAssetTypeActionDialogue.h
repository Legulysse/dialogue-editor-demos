#pragma once

#include "UnrealEd.h"
#include "Developer/AssetTools/Public/AssetTypeActions_Base.h"

//Inspired by FAssetTypeActions_DataTable
class FDemoAssetTypeActionDialogue : public FAssetTypeActions_Base
{
public:

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
	virtual uint32 GetCategories() override;
	virtual bool IsImportedAsset() const override;
	virtual UClass* GetSupportedClass() const override;

	virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override;
};
