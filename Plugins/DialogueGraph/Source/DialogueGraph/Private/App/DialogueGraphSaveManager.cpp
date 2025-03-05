#include "App/DialogueGraphSaveManager.h"
#include "DialogueGraphAsset.h"
#include "DialogueGraphRuntimeGraph.h"
#include "App/DialogueGraphApp.h"
#include "Nodes/DialogueGraphEndNode.h"
#include "Nodes/DialogueGraphInvokeNode.h"
#include "Nodes/DialogueGraphQuoteNode.h"
#include "Nodes/DialogueGraphRequestNode.h"
#include "Nodes/DialogueGraphResponseNode.h"
#include "Nodes/DialogueGraphStartNode.h"

void FDialogueGraphSaveManager::SaveGraph(UDialogueGraphAsset* asset, UEdGraph* graph)
{
	if(asset == nullptr)
	{
		UE_LOG(DialogueGraph, Warning, TEXT("Asset is null via save"));
		return;
	}
	if(graph == nullptr)
	{
		UE_LOG(DialogueGraph, Warning, TEXT("Graph is null via save"));
		return;
	}

	UDialogueGraphRuntimeGraph* runtimeGraph = NewObject<UDialogueGraphRuntimeGraph>(asset);
	asset->Graph = runtimeGraph;
	
	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UDialogueGraphRuntimePin*> idToPinMap;

	for(UEdGraphNode* uiNode : graph->Nodes)
	{
		UDialogueGraphNodeBase* dialogueNode = Cast<UDialogueGraphNodeBase>(uiNode);
		UDialogueGraphRuntimeNode* runtimeNode = NewObject<UDialogueGraphRuntimeNode>(runtimeGraph);
		
		runtimeNode->Position = FVector2D(dialogueNode->NodePosX, dialogueNode->NodePosY);
		
		for(UEdGraphPin* uiPin : dialogueNode->Pins)
		{
			UDialogueGraphRuntimePin* runtimePin = NewObject<UDialogueGraphRuntimePin>(runtimeNode);
			runtimePin->PinName = uiPin->PinName;
			runtimePin->PinId = uiPin->PinId;
			runtimePin->ParentNode = runtimeNode;
			
			if(uiPin->HasAnyConnections() && uiPin->Direction == EGPD_Output)
			{
				std::pair<FGuid, FGuid> connection = std::pair(uiPin->PinId, uiPin->LinkedTo[0]->PinId);
				connections.Add(connection);
			}

			idToPinMap.Add(uiPin->PinId, runtimePin);
			if(uiPin->Direction == EGPD_Input)
			{
				runtimeNode->InputPin = runtimePin;
			}
			else
			{
				runtimeNode->OutputPins.Add(runtimePin);
			}
		}
		
		if(dialogueNode->IsA(UDialogueGraphQuoteNode::StaticClass()))
		{
			runtimeNode->NodeType = EDialogueGraphNodeType::QuoteNode;
		}
		else if(dialogueNode->IsA(UDialogueGraphRequestNode::StaticClass()))
		{
			runtimeNode->NodeType = EDialogueGraphNodeType::RequestNode;
		}
		else if(dialogueNode->IsA(UDialogueGraphResponseNode::StaticClass()))
		{
			runtimeNode->NodeType = EDialogueGraphNodeType::ResponseNode;
		}
		else if(dialogueNode->IsA(UDialogueGraphInvokeNode::StaticClass()))
		{
			runtimeNode->NodeType = EDialogueGraphNodeType::InvokeNode;
		}
		else if(dialogueNode->IsA(UDialogueGraphEndNode::StaticClass()))
		{
			runtimeNode->NodeType = EDialogueGraphNodeType::EndNode;
		}
		else if(dialogueNode->IsA(UDialogueGraphStartNode::StaticClass()))
		{
			runtimeNode->NodeType = EDialogueGraphNodeType::StartNode;
		}
		
		runtimeNode->NodeInfo = dialogueNode->GetNodeInfo();
		runtimeGraph->Nodes.Add(runtimeNode);
	}

	for(std::pair<FGuid, FGuid> connection : connections)
	{
		UDialogueGraphRuntimePin* pin1 = *idToPinMap.Find(connection.first);
		UDialogueGraphRuntimePin* pin2 = *idToPinMap.Find(connection.second);
		pin1->Connection = pin2;
	}

	asset->Modify();
}

void FDialogueGraphSaveManager::LoadGraph(UDialogueGraphAsset* asset, UEdGraph* graph)
{
	if(asset->Graph == nullptr)
	{
		graph->GetSchema()->CreateDefaultNodesForGraph(*graph);
		return;
	}

	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UEdGraphPin*> idToPinMap;
	
	for(UDialogueGraphRuntimeNode* runtimeNode : asset->Graph->Nodes)
	{
		UDialogueGraphNodeBase* uiNode = nullptr;

		switch(runtimeNode->NodeType)
		{
			case EDialogueGraphNodeType::QuoteNode:
				uiNode = NewObject<UDialogueGraphQuoteNode>(graph);
				break;
			
			case EDialogueGraphNodeType::StartNode:
				uiNode = NewObject<UDialogueGraphStartNode>(graph);
				break;
			
			case EDialogueGraphNodeType::EndNode:
				uiNode = NewObject<UDialogueGraphEndNode>(graph);
				break;

			case EDialogueGraphNodeType::RequestNode:
				uiNode = NewObject<UDialogueGraphRequestNode>(graph);
				break;
			
			case EDialogueGraphNodeType::ResponseNode:
				uiNode = NewObject<UDialogueGraphResponseNode>(graph);
				break;

			case EDialogueGraphNodeType::InvokeNode:
				uiNode = NewObject<UDialogueGraphInvokeNode>(graph);
				break;
			
			default:
				UE_LOG(DialogueGraph, Error, TEXT("FDialogueGraphApp::UpdateEditorGraphFromWorkingAsset: Unknown node type"));
				continue;
		}
		
		uiNode->CreateNewGuid();
		uiNode->NodePosX = runtimeNode->Position.X;
		uiNode->NodePosY = runtimeNode->Position.Y;

		if(runtimeNode->NodeInfo != nullptr)
		{
			uiNode->SetNodeInfo(DuplicateObject(runtimeNode->NodeInfo, runtimeNode));
		}
		else if(runtimeNode->NodeType != EDialogueGraphNodeType::StartNode)
		{
			uiNode->SetNodeInfo(NewObject<UDialogueGraphQuoteNodeInfo>(runtimeNode));
		}
		
		if(runtimeNode->InputPin != nullptr)
		{
			UDialogueGraphRuntimePin* inputPin = runtimeNode->InputPin;
			UEdGraphPin* uiPin = uiNode->CreateGraphPin(EGPD_Input, inputPin->PinName);
			uiPin->PinId = inputPin->PinId;
			
			idToPinMap.Add(inputPin->PinId, uiPin);
		}
		
		for (UDialogueGraphRuntimePin* outputPin : runtimeNode->OutputPins)
		{
			UEdGraphPin* uiPin = uiNode->CreateGraphPin(EGPD_Output, outputPin->PinName);
			uiPin->PinId = outputPin->PinId;

			if(outputPin->Connection != nullptr)
			{
				connections.Add(std::make_pair(outputPin->PinId, outputPin->Connection->PinId));
			}
			idToPinMap.Add(outputPin->PinId, uiPin);
		}

		graph->AddNode(uiNode, true, false);
		
		for (std::pair<FGuid, FGuid> connection : connections)
		{
			UEdGraphPin** fromPinPtr = idToPinMap.Find(connection.first);
			UEdGraphPin** toPinPtr = idToPinMap.Find(connection.second);

			if (fromPinPtr != nullptr && toPinPtr != nullptr)
			{
				UEdGraphPin* fromPin = *fromPinPtr;
				UEdGraphPin* toPin = *toPinPtr;

				if (fromPin != nullptr && toPin != nullptr)
				{
					fromPin->LinkedTo.Add(toPin);
					toPin->LinkedTo.Add(fromPin);
				}
			}
		}
	}

	graph->Modify();
}
