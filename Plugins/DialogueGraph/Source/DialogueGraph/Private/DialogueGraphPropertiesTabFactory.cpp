#include "DialogueGraphPropertiesTabFactory.h"
#include "App/DialogueGraphApp.h"
#include "DialogueGraphAsset.h"

FDialogueGraphPropertiesTabFactory::FDialogueGraphPropertiesTabFactory(TSharedPtr<FDialogueGraphApp> app) : FWorkflowTabFactory(FName("DialogueGraphPropertiesTab"), app)
{
	_app = app;
	TabLabel = FText::FromString(TEXT("Properties"));
	ViewMenuDescription = FText::FromString(TEXT("Displays Properties"));
	ViewMenuTooltip = FText::FromString(TEXT("Show Properties"));
}

TSharedRef<SWidget> FDialogueGraphPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& info) const
{
	TSharedPtr<FDialogueGraphApp> app = _app.Pin();
	FPropertyEditorModule& propertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs detailsViewArgs;
	{
		detailsViewArgs.bAllowSearch = false;
		detailsViewArgs.bHideSelectionTip = true;
		detailsViewArgs.bLockable = false;
		detailsViewArgs.bSearchInitialKeyFocus = true;
		detailsViewArgs.bUpdatesFromSelection = true;
		detailsViewArgs.NotifyHook = nullptr;
		detailsViewArgs.bShowOptions = true;
		detailsViewArgs.bShowModifiedPropertiesOption = false;
		detailsViewArgs.bShowScrollBar = false;
	}

	
	
	TSharedPtr<IDetailsView> selectedNodeDetailsView = propertyEditorModule.CreateDetailView(detailsViewArgs);
	selectedNodeDetailsView->SetObject(nullptr);
	
	app->SetSelectedNodeDetailView(selectedNodeDetailsView);

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(FMargin(10, 5))
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Assign Nodes ID")))
			.OnClicked_Lambda([app]() -> FReply
			{
				app->UpdateNodesId();
				
				return FReply::Handled(); 
			})
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		[
			selectedNodeDetailsView.ToSharedRef()
		];
}

FText FDialogueGraphPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("Properties Are Properties."));
}