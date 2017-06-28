// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DialogueDemoUnrealEditor.h"
#include "Modules/ModuleManager.h"
#include "DemoAssetTypeActionDialogue.h"

IMPLEMENT_MODULE( IDemoDialogueEditor, DemoDialogueEditor);
 
void IDemoDialogueEditor::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FDemoAssetTypeActionDialogue));
}

void IDemoDialogueEditor::ShutdownModule()
{
}
