#include "DemoDialogueFactory.h"

#include "DialogueDemoUnreal/Assets/DemoDialogue.h"

#include "AssetRegistryModule.h"
#include "Json.h"
//#include "JsonUtilities.h"

UDemoDialogueFactory::UDemoDialogueFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UDemoDialogue::StaticClass();
	Formats.Add(TEXT("dlg;Dialogue"));
	bCreateNew = false;
	bEditorImport = true;
	bEditAfterNew = true;
	bText = true;
}

//Inspired by UCSVImportFactory::FactoryCreateText
UObject* UDemoDialogueFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

	UDemoDialogue* NewAsset = NewObject<UDemoDialogue>(InParent, InName, Flags | RF_Transactional);
    NewAsset->AssetImportData = NewObject<UAssetImportData>(NewAsset, TEXT("AssetImportData"));

	const FString CurrentFilename = UFactory::GetCurrentFilename();
	FString CurrentSourcePath;
	FString FilenameNoExtension;
	FString UnusedExtension;
	FPaths::Split(CurrentFilename, CurrentSourcePath, FilenameNoExtension, UnusedExtension);

	// Convert buffer to an FString (will this be slow with big tables?)
	FString String;
	//const int32 BufferSize = BufferEnd - Buffer;
	//appBufferToString( String, Buffer, BufferSize );
	int32 NumChars = (BufferEnd - Buffer);
	TArray<TCHAR>& StringChars = String.GetCharArray();
	StringChars.AddUninitialized(NumChars + 1);
	FMemory::Memcpy(StringChars.GetData(), Buffer, NumChars*sizeof(TCHAR));
	StringChars.Last() = 0;

	NewAsset->AssetImportData->Update(CurrentFilename);

	LoadFromText(NewAsset, String);

	FEditorDelegates::OnAssetPostImport.Broadcast(this, NewAsset);

	return NewAsset;
}

void UDemoDialogueFactory::LoadFromText(UDemoDialogue* InDialogue, const FString& JSonContent)
{
	static const FName AssetRegistryName("AssetRegistry");
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryName);
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	
	TSharedPtr< FJsonObject > JsonFile;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JSonContent);

	if (FJsonSerializer::Deserialize(Reader, JsonFile) && JsonFile.IsValid())
	{
	}
}

bool UDemoDialogueFactory::FactoryCanImport(const FString& Filename)
{
	return FCString::Stricmp(*FPaths::GetExtension(Filename), TEXT("dlg")) == 0;
}

bool UDemoDialogueFactory::DoesSupportClass(UClass * Class)
{
	return (Class == UDemoDialogue::StaticClass());
}

bool UDemoDialogueFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	UDemoDialogue* Dialogue = Cast<UDemoDialogue>(Obj);
    if (Dialogue)
    {
        if (Dialogue->AssetImportData)
        {
            OutFilenames.Add(Dialogue->AssetImportData->GetFirstFilename());
        }
        else
        {
            OutFilenames.Add(TEXT(""));
        }
        return true;
    }
    return false;
}

void UDemoDialogueFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	UDemoDialogue* Dialogue = Cast<UDemoDialogue>(Obj);
    if (Dialogue && ensure(NewReimportPaths.Num() == 1))
    {
        Dialogue->AssetImportData->UpdateFilenameOnly(NewReimportPaths[0]);
    }
}

EReimportResult::Type UDemoDialogueFactory::Reimport(UObject* Obj)
{
	UDemoDialogue* Dialogue = Cast<UDemoDialogue>(Obj);
	if (!Dialogue)
	{
		return EReimportResult::Failed;
	}

    FString Path;
    if (Dialogue->AssetImportData->ExtractFilenames().Num() > 0)
        Path = Dialogue->AssetImportData->ExtractFilenames().Top();
	if (Path.IsEmpty() == false)
	{
		FString FilePath = IFileManager::Get().ConvertToRelativePath(*Path);

		FString Data;
		if (FFileHelper::LoadFileToString(Data, *FilePath))
		{
            Dialogue->AssetImportData->Update(Dialogue->AssetImportData->GetFirstFilename());

			LoadFromText(Dialogue, Data);

            if (Dialogue->GetOuter())
                Dialogue->GetOuter()->MarkPackageDirty();
            else
                Dialogue->MarkPackageDirty();

            FEditorDelegates::OnAssetPostImport.Broadcast(this, Dialogue);

			return EReimportResult::Succeeded;
		}
	}

	return EReimportResult::Failed;
}
