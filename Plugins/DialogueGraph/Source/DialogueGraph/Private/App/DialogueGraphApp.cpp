#include "App/DialogueGraphApp.h"
#include "App/DialogueGraphAppMode.h"
#include "DialogueGraphAsset.h"
#include "DialogueGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Nodes/DialogueGraphStartNode.h"

DEFINE_LOG_CATEGORY(DialogueGraph)

void FDialogueGraphApp::RegisterTabSpawners(const TSharedRef<FTabManager>& tabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(tabManager);
}

void FDialogueGraphApp::InitEditor(const EToolkitMode::Type mode, const TSharedPtr<IToolkitHost>& initToolkitHost,UObject* inObject)
{
	TArray<UObject*> objectsToEdit;
	objectsToEdit.Add(inObject);

	_workingAsset = Cast<UDialogueGraphAsset>(inObject);
	
	_workingGraph = FBlueprintEditorUtils::CreateNewGraph (
		_workingAsset,
		NAME_None,
		UEdGraph::StaticClass(),
		UDialogueGraphSchema::StaticClass()
	);
	
	InitAssetEditor (
		mode,
		initToolkitHost,
		TEXT("DialogueGraphApp"),
		FTabManager::FLayout::NullLayout,
		true,
		true,
		objectsToEdit
	); 

	AddApplicationMode(TEXT("DialogueGraphAppMode"), MakeShareable(new FDialogueGraphAppMode(SharedThis(this))));

	SetCurrentMode(TEXT("DialogueGraphAppMode"));

	FDialogueGraphSaveManager::LoadGraph(_workingAsset, _workingGraph);
}

void FDialogueGraphApp::SetSelectedNodeDetailView(TSharedPtr<IDetailsView> detailsView)
{
	_selectedNodeDetailView = detailsView;
	_selectedNodeDetailView->OnFinishedChangingProperties().AddRaw(this, &FDialogueGraphApp::OnNodeDetailsViewPropertiesUpdated);
}

void FDialogueGraphApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& selection)
{
	//find the first UDialogueNode if any
	for(UObject* obj : selection)
	{
		UDialogueGraphNodeBase* node = Cast<UDialogueGraphNodeBase>(obj);

		if(node != nullptr && node->GetNodeInfo() != nullptr)
		{
			_selectedNodeDetailView->SetObject(node->GetNodeInfo());
			return;
		}
	}
	
	_selectedNodeDetailView->SetObject(nullptr);
}

void FDialogueGraphApp::OnNodeDetailsViewPropertiesUpdated(const FPropertyChangedEvent& event)
{
	if(_workingGraphUi != nullptr)
	{
		_workingGraph->NotifyGraphChanged();
	}
}

void FDialogueGraphApp::UpdateNodesId()
{
	for(uint64 i = 0; i <  _workingGraph->Nodes.Num(); i++)
	{
		if(Cast<UDialogueGraphNodeBase>(_workingGraph->Nodes[i])->GetNodeInfo() != nullptr)
		{
			Cast<UDialogueGraphNodeBase>(_workingGraph->Nodes[i])->SetInfoNodeId(i+1);
		}		
	}
}
