#include "DialogueGraphPrimaryTabFactory.h"
#include "App/DialogueGraphApp.h"

FDialogueGraphPrimaryTabFactory::FDialogueGraphPrimaryTabFactory(TSharedPtr<FDialogueGraphApp> app) : FWorkflowTabFactory(FName("DialogueGraphPrimaryTab"), app)
{
	_app = app;
	TabLabel = FText::FromString(TEXT("Graph"));
	ViewMenuDescription = FText::FromString(TEXT("Displays Main Graph"));
	ViewMenuTooltip = FText::FromString(TEXT("Show The Main Graph"));
}

TSharedRef<SWidget> FDialogueGraphPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& info) const
{
	TSharedPtr<FDialogueGraphApp> app = _app.Pin();

	SGraphEditor::FGraphEditorEvents graphEvents;
	graphEvents.OnSelectionChanged.BindRaw(app.Get(), &FDialogueGraphApp::OnGraphSelectionChanged);
	
	TSharedPtr<SGraphEditor> graphEditor =
		SNew(SGraphEditor)
			.IsEditable(true)
			.GraphEvents(graphEvents)
			.GraphToEdit(app->GetWorkingGraph());

	app->SetWorkingGraphUi(graphEditor);
	
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1)
		.HAlign(HAlign_Fill)
		[
			graphEditor.ToSharedRef()
		];
}

FText FDialogueGraphPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("Primary view doing primary things."));
}