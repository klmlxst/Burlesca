// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueGraph.h"
#include "DialogueGraphAction.h"
#include "EdGraphUtilities.h"
#include "IAssetTools.h"
#include "Interfaces/IPluginManager.h"
#include "Pins/DialogueGraphPinFactory.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FDialogueGraphModule"

void FDialogueGraphModule::StartupModule()
{
	IAssetTools& assetToolsModule = IAssetTools::Get();
	EAssetTypeCategories::Type assetType = assetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("Dialogue")), FText::FromString("Dialogue"));
	TSharedPtr<FDialogueGraphAction> dialogueGraphAction = MakeShareable(new FDialogueGraphAction(assetType));
	assetToolsModule.RegisterAssetTypeActions(dialogueGraphAction.ToSharedRef());

	_styleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogueGraphStyle")));
	TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin(TEXT("DialogueGraph"));
	FString contentDir = plugin->GetContentDir();
	_styleSet->SetContentRoot(contentDir);

	FSlateImageBrush* thumbnailBrush = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("DialogueGraphAssetThumbnail"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* iconBrush = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("DialogueGraphAssetIcon"), TEXT(".png")), FVector2D(128, 128));
	_styleSet->Set(TEXT("ClassThumbnail.DialogueGraphAsset"), thumbnailBrush);
	_styleSet->Set(TEXT("ClassIcon.DialogueGraphAsset"), iconBrush);
	
	FSlateImageBrush* nodeAddPinIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("AddPinIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* nodeDeletePinIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("DeletePinIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* deleteNodeIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("DeleteNodeIcon"), TEXT(".png")), FVector2D(128, 128));
	_styleSet->Set(TEXT("DialogueGraph.NodeAddPinIcon"), nodeAddPinIcon);
	_styleSet->Set(TEXT("DialogueGraph.NodeDeletePinIcon"), nodeDeletePinIcon);
	_styleSet->Set(TEXT("DialogueGraph.DeleteNodeIcon"), deleteNodeIcon);
	
	FSlateStyleRegistry::RegisterSlateStyle(*_styleSet);

	_pinFactory = MakeShareable(new FDialogueGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(_pinFactory);
}

void FDialogueGraphModule::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*_styleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(_pinFactory);
}	

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueGraphModule, DialogueGraph)