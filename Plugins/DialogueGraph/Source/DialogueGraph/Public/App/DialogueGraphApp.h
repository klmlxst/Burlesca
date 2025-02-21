#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphSaveManager.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UDialogueGraphAsset;

class FDialogueGraphApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	void InitEditor(const EToolkitMode::Type mode, const TSharedPtr<IToolkitHost>& initToolkitHost, UObject* inObject);

	UDialogueGraphAsset* GetWorkingAsset() { return _workingAsset; }
	UEdGraph* GetWorkingGraph() { return _workingGraph; }

	void SetWorkingGraphUi(TSharedPtr<SGraphEditor> workingGraphUi) { _workingGraphUi = workingGraphUi; }
	void SetSelectedNodeDetailView(TSharedPtr<IDetailsView> detailsView);
	void OnGraphSelectionChanged(const FGraphPanelSelectionSet& selection);
	void OnNodeDetailsViewPropertiesUpdated(const FPropertyChangedEvent& event);
	void UpdateNodesId();
	//FAssetToolkit interface

	virtual FName GetToolkitFName() const override { return FName(TEXT("DialogueGraphApp")); }
	virtual FText GetToolkitName() const override { return FText::FromString("DialogueGraphApp"); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("DialogueGraphApp"); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DialogueGraphApp"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.35f, 0.2f, 0.5f, 0.5f); }
	virtual FString GetDocumentationLink() const override { return TEXT("///  ??  TODO  ??  ///"); }

	virtual	void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override { FWorkflowCentricApplication::OnToolkitHostingStarted(Toolkit); }
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override { FWorkflowCentricApplication::OnToolkitHostingFinished(Toolkit); }

	virtual void SaveAsset_Execute() override { FWorkflowCentricApplication::SaveAsset_Execute(); FDialogueGraphSaveManager::SaveGraph(_workingAsset, _workingGraph); }

private:
	UPROPERTY()
	UDialogueGraphAsset* _workingAsset = nullptr;
	
	//graph model
	UPROPERTY()
	UEdGraph* _workingGraph = nullptr;

	//graph ui view
	TSharedPtr<SGraphEditor> _workingGraphUi = nullptr;

	TSharedPtr<IDetailsView> _selectedNodeDetailView = nullptr;
};
