#include "DemoAssetTypeActionDialogue.h"

#include "DialogueDemoUnreal/Assets/DemoDialogue.h"


FText FDemoAssetTypeActionDialogue::GetName() const 
{
	return FText::FromString(TEXT("Dialogue Asset"));
}

FColor FDemoAssetTypeActionDialogue::GetTypeColor() const
{
	return FColor(255, 255, 255);
}

bool FDemoAssetTypeActionDialogue::HasActions(const TArray<UObject*>& InObjects) const 
{
	return true; 
}

uint32 FDemoAssetTypeActionDialogue::GetCategories()
{
	return EAssetTypeCategories::Misc; 
}

bool FDemoAssetTypeActionDialogue::IsImportedAsset() const
{
	return true; 
}

UClass* FDemoAssetTypeActionDialogue::GetSupportedClass() const
{
	return UDemoDialogue::StaticClass();
}

void FDemoAssetTypeActionDialogue::GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const
{
    for (auto& Asset : TypeAssets)
    {
        const auto Dialogue = CastChecked<UDemoDialogue>(Asset);

        FString GameDir = FPaths::ProjectContentDir();
        FString CurrentFilenameRelative = Dialogue->ImportPath.Path;
        FString Path = FPaths::ConvertRelativePathToFull(GameDir, CurrentFilenameRelative);

        OutSourceFilePaths.Add(Path);
    }
}
