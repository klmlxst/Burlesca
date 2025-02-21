#include "DialogueGraphAction.h"
#include "DialogueGraphAsset.h"
#include "App/DialogueGraphApp.h"

FDialogueGraphAction::FDialogueGraphAction(EAssetTypeCategories::Type category)
{
	_assetCategory = category;
}

FText FDialogueGraphAction::GetName() const
{
	return FText::FromString("Dialogue Graph");
}

FColor FDialogueGraphAction::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FDialogueGraphAction::GetSupportedClass() const
{
	return UDialogueGraphAsset::StaticClass();
}

void FDialogueGraphAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);

	EToolkitMode::Type mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for(UObject* object : InObjects)
	{
		UDialogueGraphAsset* asset = Cast<UDialogueGraphAsset>(object);
		if(asset != nullptr)
		{
			TSharedRef<FDialogueGraphApp> editor(new FDialogueGraphApp());
			editor->InitEditor(mode, EditWithinLevelEditor, asset);
		}
	}
}

uint32 FDialogueGraphAction::GetCategories()
{
	return _assetCategory;
}
