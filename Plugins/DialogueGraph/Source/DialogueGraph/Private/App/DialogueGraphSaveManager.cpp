#include "App/DialogueGraphSaveManager.h"
#include "DialogueGraphAsset.h"
#include "DialogueGraphRuntimeGraph.h"
#include "Nodes/DialogueGraphEndNode.h"
#include "Nodes/DialogueGraphInvokeNode.h"
#include "Nodes/DialogueGraphQuoteNode.h"
#include "Nodes/DialogueGraphRequestNode.h"
#include "Nodes/DialogueGraphResponseNode.h"
#include "Nodes/DialogueGraphStartNode.h"

DEFINE_LOG_CATEGORY_STATIC(DialogueGraph, Log, All)

void FDialogueGraphSaveManager::SaveGraph(UDialogueGraphAsset* asset, UEdGraph* graph)
{
	if(asset == nullptr || graph == nullptr)
	{
		return;
	}

	UDialogueGraphRuntimeGraph* runtimeGraph = NewObject<UDialogueGraphRuntimeGraph>(asset);
	asset->Graph = runtimeGraph;

	TArray<std::pair<FGuid, FGuid>> connections;
	TMap<FGuid, UDialogueGraphRuntimePin*> idToPinMap;

	for(UEdGraphNode* uiNode : graph->Nodes)
	{		
		UDialogueGraphRuntimeNode* runtimeNode = NewObject<UDialogueGraphRuntimeNode>(runtimeGraph);
		runtimeNode->Position = FVector2D(uiNode->NodePosX, uiNode->NodePosY);
		
		for(UEdGraphPin* uiPin : uiNode->Pins)
		{
			UDialogueGraphRuntimePin* runtimePin = NewObject<UDialogueGraphRuntimePin>(runtimeNode);
			runtimePin->PinName = uiPin->PinName;
			runtimePin->PinId = uiPin->PinId;

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
		
		if(uiNode->IsA(UDialogueGraphQuoteNode::StaticClass()))
		{
			UDialogueGraphQuoteNode* quoteNode = Cast<UDialogueGraphQuoteNode>(uiNode);
			runtimeNode->NodeType = EDialogueGraphNodeType::QuoteNode;
			runtimeNode->NodeInfo = quoteNode->GetNodeInfo();
		}
		else if(uiNode->IsA(UDialogueGraphEndNode::StaticClass()))
		{
			UDialogueGraphEndNode* endNode = Cast<UDialogueGraphEndNode>(uiNode);
			runtimeNode->NodeType = EDialogueGraphNodeType::EndNode;
			runtimeNode->NodeInfo = endNode->GetNodeInfo();
		}
		else if(uiNode->IsA(UDialogueGraphStartNode::StaticClass()))
		{
			runtimeNode->NodeType = EDialogueGraphNodeType::StartNode;
		}

		runtimeGraph->Nodes.Add(runtimeNode);
	}

	for(std::pair<FGuid, FGuid> connection : connections)
	{
		UDialogueGraphRuntimePin* pin1 = *idToPinMap.Find(connection.first);
		UDialogueGraphRuntimePin* pin2 = *idToPinMap.Find(connection.second);
		pin1->Connection = pin2;
		UE_LOG(LogTemp, Warning, TEXT("called save connection"))
	}
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

			case EDialogueGraphNodeType::Unknown:
				UE_LOG(DialogueGraph, Error, TEXT("FDialogueGraphApp::UpdateEditorGraphFromWorkingAsset: Unknown node type"));
				continue;
			
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
}
