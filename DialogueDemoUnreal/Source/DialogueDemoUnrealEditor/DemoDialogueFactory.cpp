#include "DemoDialogueFactory.h"

#include "DialogueDemoUnreal/Assets/DemoDialogue.h"
#include "DialogueDemoUnreal/Assets/DemoDialogueNode.h"
#include "DialogueDemoUnreal/Assets/DemoDialogueNodeBranch.h"
#include "DialogueDemoUnreal/Assets/DemoDialogueNodeChoice.h"
#include "DialogueDemoUnreal/Assets/DemoDialogueNodeGoto.h"
#include "DialogueDemoUnreal/Assets/DemoDialogueNodeReply.h"
#include "DialogueDemoUnreal/Assets/DemoDialogueNodeRoot.h"
#include "DialogueDemoUnreal/Assets/DemoDialogueNodeSentence.h"
#include "DialogueDemoUnreal/Assets/Actions/DemoNodeAction.h"
#include "DialogueDemoUnreal/Assets/Conditions/DemoNodeCondition.h"
#include "DialogueDemoUnreal/Assets/Conditions/DemoNodeConditionGroup.h"
#include "DialogueDemoUnreal/Assets/Conditions/DemoNodeConditionGroupAnd.h"
#include "DialogueDemoUnreal/Assets/Conditions/DemoNodeConditionGroupOr.h"
#include "DialogueDemoUnreal/Assets/Flags/DemoNodeFlag.h"

//#include "AssetRegistryModule.h"
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
	//static const FName AssetRegistryName("AssetRegistry");
	//FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryName);
	//IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	
	TSharedPtr< FJsonObject > JsonFile;
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JSonContent);

	if (FJsonSerializer::Deserialize(Reader, JsonFile) && JsonFile.IsValid())
	{
        //Reset Asset
        InDialogue->RootNode = nullptr;
        InDialogue->ListNodes.Empty();

        //Parse JSon
        JsonFile->TryGetStringField("Version", InDialogue->Version);
        JsonFile->TryGetNumberField("RootNodeID", InDialogue->RootNodeID);

        FString SceneType = "";
        JsonFile->TryGetStringField("SceneType", SceneType);
        if (SceneType == "Interactive")
            InDialogue->SceneType = EDemoDialogueSceneType::Interactive;
        else if (SceneType == "Cinematic")
            InDialogue->SceneType = EDemoDialogueSceneType::Cinematic;
        else if (SceneType == "Ambient")
            InDialogue->SceneType = EDemoDialogueSceneType::Ambient;
        else if (SceneType == "Monologue")
            InDialogue->SceneType = EDemoDialogueSceneType::Monologue;

        JsonFile->TryGetStringField("VoiceBank", InDialogue->VoiceBank);

        const TArray< TSharedPtr<FJsonValue> > * JSonListNodes;
        JsonFile->TryGetArrayField("ListNodes", JSonListNodes);
        for (TSharedPtr<FJsonValue> JSonNodeValue : *JSonListNodes)
        {
            const TSharedPtr<FJsonObject> * JSonNodePtr = nullptr;
            if (!JSonNodeValue->TryGetObject(JSonNodePtr))
                continue;

            const TSharedPtr<FJsonObject> JSonNode = *JSonNodePtr;

            FString NodeTypeName;
            JSonNode->TryGetStringField("$type", NodeTypeName);

            UDemoDialogueNode* NewNode = nullptr;

            if (NodeTypeName == "NodeRoot")
            {
                UDemoDialogueNodeRoot* NodeRoot = NewObject<UDemoDialogueNodeRoot>(InDialogue);
                NewNode = NodeRoot;
            }
            else if (NodeTypeName == "NodeSentence")
            {
                UDemoDialogueNodeSentence* NodeSentence = NewObject<UDemoDialogueNodeSentence>(InDialogue);

                JSonNode->TryGetStringField("Sentence", NodeSentence->Sentence);
                JSonNode->TryGetStringField("SpeakerID", NodeSentence->SpeakerID);
                JSonNode->TryGetStringField("ListenerID", NodeSentence->ListenerID);

                JSonNode->TryGetStringField("VoicingID", NodeSentence->VoicingID);
                JSonNode->TryGetBoolField("HideSubtitle", NodeSentence->bHideSubtitle);

                JSonNode->TryGetStringField("SpeakerAnimset", NodeSentence->SpeakerAnimset);
                JSonNode->TryGetStringField("ListenerAnimset", NodeSentence->ListenerAnimset);
                JSonNode->TryGetStringField("SpeakerAnim", NodeSentence->SpeakerAnim);
                JSonNode->TryGetStringField("ListenerAnim", NodeSentence->ListenerAnim);

                NewNode = NodeSentence;

            }
            else if (NodeTypeName == "NodeChoice")
            {
                UDemoDialogueNodeChoice* NodeChoice = NewObject<UDemoDialogueNodeChoice>(InDialogue);

                const TArray< TSharedPtr<FJsonValue> > * JSonRepliesIDs;
                JSonNode->TryGetArrayField("RepliesIDs", JSonRepliesIDs);
                for (TSharedPtr<FJsonValue> JSonReplyIDValue : *JSonRepliesIDs)
                {
                    int32 ReplyID = -1;
                    if (JSonReplyIDValue->TryGetNumber(ReplyID))
                        NodeChoice->RepliesIDs.Add(ReplyID);
                }

                NewNode = NodeChoice;
            }
            else if (NodeTypeName == "NodeReply")
            {
                UDemoDialogueNodeReply* NodeReply = NewObject<UDemoDialogueNodeReply>(InDialogue);
                JSonNode->TryGetStringField("Reply", NodeReply->Reply);
                NewNode = NodeReply;
            }
            else if (NodeTypeName == "NodeGoto")
            {
                UDemoDialogueNodeGoto* NodeGoto = NewObject<UDemoDialogueNodeGoto>(InDialogue);
                JSonNode->TryGetNumberField("GotoID", NodeGoto->GotoID);
                NewNode = NodeGoto;
            }
            else if (NodeTypeName == "NodeBranch")
            {
                UDemoDialogueNodeBranch* NodeBranch = NewObject<UDemoDialogueNodeBranch>(InDialogue);
                JSonNode->TryGetNumberField("BranchID", NodeBranch->BranchID);
                NewNode = NodeBranch;
            }

            if (NewNode)
            {
                //Parse Common
                JSonNode->TryGetNumberField("ID", NewNode->ID);
                JSonNode->TryGetNumberField("NextID", NewNode->NextID);

                InDialogue->ListNodes.Add(NewNode);

                //Parse Conditions
                const TArray< TSharedPtr<FJsonValue> > * JSonConditions;
                if (JSonNode->TryGetArrayField("Conditions", JSonConditions))
                {
                    for (TSharedPtr<FJsonValue> JSonConditionValue : *JSonConditions)
                    {
                        const TSharedPtr<FJsonObject> * JSonConditionPtr = nullptr;
                        if (!JSonConditionValue->TryGetObject(JSonConditionPtr))
                            continue;

                        const TSharedPtr<FJsonObject> JSonCondition = *JSonConditionPtr;

                        UDemoNodeCondition* NewCondition = ParseCondition(JSonCondition, NewNode);
                        if (NewCondition)
                        {
                            NewNode->Conditions.Add(NewCondition);
                        }
                    }
                }

                //Parse Actions
                const TArray< TSharedPtr<FJsonValue> > * JSonActions;
                if (JSonNode->TryGetArrayField("Actions", JSonActions))
                {
                    for (TSharedPtr<FJsonValue> JSonActionValue : *JSonActions)
                    {
                        const TSharedPtr<FJsonObject> * JSonActionPtr = nullptr;
                        if (!JSonActionValue->TryGetObject(JSonActionPtr))
                            continue;

                        const TSharedPtr<FJsonObject> JSonAction = *JSonActionPtr;

                        FString ActionTypeName;
                        JSonAction->TryGetStringField("$type", ActionTypeName);

                        UDemoNodeAction* NewAction = nullptr;

                        // TODO: All Actions

                        if (NewAction)
                        {
                            JSonAction->TryGetBoolField("OnNodeStart", NewAction->bOnNodeStart);
                            NewNode->Actions.Add(NewAction);
                        }
                    }
                }

                //Parse Flags
                const TArray< TSharedPtr<FJsonValue> > * JSonFlags;
                if (JSonNode->TryGetArrayField("Flags", JSonFlags))
                {
                    for (TSharedPtr<FJsonValue> JSonFlagValue : *JSonFlags)
                    {
                        const TSharedPtr<FJsonObject> * JSonFlagPtr = nullptr;
                        if (!JSonFlagValue->TryGetObject(JSonFlagPtr))
                            continue;

                        const TSharedPtr<FJsonObject> JSonFlag = *JSonFlagPtr;

                        FString FlagTypeName;
                        JSonFlag->TryGetStringField("$type", FlagTypeName);

                        UDemoNodeFlag* NewFlag = nullptr;

                        // TODO: All Flags

                        if (NewFlag)
                        {
                            NewNode->Flags.Add(NewFlag);
                        }
                    }
                }
            }
        }

        //Resolve Links
        InDialogue->RootNode = InDialogue->GetNodeByID(InDialogue->RootNodeID);
        for (UDemoDialogueNode* Node : InDialogue->ListNodes)
        {
            Node->Next = InDialogue->GetNodeByID(Node->NextID);

            //if (Node->IsA(UDemoDialogueNodeRoot::StaticClass))
            //if (Node->IsA(UDemoDialogueNodeSentence::StaticClass))
            if (Node->IsA(UDemoDialogueNodeChoice::StaticClass()))
            {
                UDemoDialogueNodeChoice* Choice = Cast<UDemoDialogueNodeChoice>(Node);
                for (int32 ReplyID : Choice->RepliesIDs)
                {
                    UDemoDialogueNodeReply* Reply = Cast<UDemoDialogueNodeReply>(InDialogue->GetNodeByID(ReplyID));
                    if (Reply)
                        Choice->Replies.Add(Reply);
                }
            }
            //if (Node->IsA(UDemoDialogueNodeReply::StaticClass))
            else if (Node->IsA(UDemoDialogueNodeGoto::StaticClass()))
            {
                UDemoDialogueNodeGoto* Goto = Cast<UDemoDialogueNodeGoto>(Node);
                Goto->Goto = InDialogue->GetNodeByID(Goto->GotoID);
            }
            else if (Node->IsA(UDemoDialogueNodeBranch::StaticClass()))
            {
                UDemoDialogueNodeBranch* Branch = Cast<UDemoDialogueNodeBranch>(Node);
                Branch->Branch = InDialogue->GetNodeByID(Branch->BranchID);
            }
        }
	}
}

void UDemoDialogueFactory::ParseGroupConditions(const TSharedPtr<FJsonObject> JSonConditionGroup, UDemoNodeConditionGroup* NewConditionGroup)
{
    const TArray< TSharedPtr<FJsonValue> > * JSonConditions;
    if (JSonConditionGroup->TryGetArrayField("Conditions", JSonConditions))
    {
        for (TSharedPtr<FJsonValue> JSonConditionValue : *JSonConditions)
        {
            const TSharedPtr<FJsonObject> * JSonConditionPtr = nullptr;
            if (!JSonConditionValue->TryGetObject(JSonConditionPtr))
                continue;

            const TSharedPtr<FJsonObject> JSonCondition = *JSonConditionPtr;

            UDemoNodeCondition* NewCondition = ParseCondition(JSonCondition, NewConditionGroup);
            if (NewCondition)
            {
                NewConditionGroup->Conditions.Add(NewCondition);
            }
        }
    }
}

UDemoNodeCondition* UDemoDialogueFactory::ParseCondition(const TSharedPtr<FJsonObject> JSonCondition, UObject* Outer)
{
    FString ConditionTypeName;
    JSonCondition->TryGetStringField("$type", ConditionTypeName);

    UDemoNodeCondition* NewCondition = nullptr;

    if (ConditionTypeName == "ConditionAnd")
    {
        UDemoNodeConditionGroupAnd* NewConditionGroupAnd = NewObject<UDemoNodeConditionGroupAnd>(Outer);
        ParseGroupConditions(JSonCondition, NewConditionGroupAnd);
        NewCondition = NewConditionGroupAnd;
    }
    else if (ConditionTypeName == "ConditionOr")
    {
        UDemoNodeConditionGroupOr* NewConditionGroupOr = NewObject<UDemoNodeConditionGroupOr>(Outer);
        ParseGroupConditions(JSonCondition, NewConditionGroupOr);
        NewCondition = NewConditionGroupOr;
    }

    // TODO: All Conditions

    //Common
    if (NewCondition)
    {
        JSonCondition->TryGetBoolField("IntendedResult", NewCondition->bIntendedResult);
    }

    return NewCondition;
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
