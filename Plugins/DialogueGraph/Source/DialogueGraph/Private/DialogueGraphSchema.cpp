#include "DialogueGraphSchema.h"

#include "Nodes/DialogueGraphEndNode.h"
#include "Nodes/DialogueGraphInvokeNode.h"
#include "Nodes/DialogueGraphQuoteNode.h"
#include "Nodes/DialogueGraphRequestNode.h"
#include "Nodes/DialogueGraphResponseNode.h"
#include "Nodes/DialogueGraphStartNode.h"

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const
{
	TSharedPtr<FDialogueGraphNewNodeAction> newQuoteNodeAction (
		new FDialogueGraphNewNodeAction (
			UDialogueGraphQuoteNode::StaticClass(),
			FText::FromString("Nodes"),
			FText::FromString("QuoteNode"),
			FText::FromString("Makes a node for companion quote"),
			0
		)
	);

	TSharedPtr<FDialogueGraphNewNodeAction> newEndNodeAction (
		new FDialogueGraphNewNodeAction (
			UDialogueGraphEndNode::StaticClass(),
			FText::FromString("Nodes"),
			FText::FromString("EndNode"),
			FText::FromString("Makes a node for end dialogue"),
			0
		)
	);

	TSharedPtr<FDialogueGraphNewNodeAction> newRequestNodeAction (
		new FDialogueGraphNewNodeAction (
			UDialogueGraphRequestNode::StaticClass(),
			FText::FromString("Nodes"),
			FText::FromString("RequestNode"),
			FText::FromString("Makes a node for giving player an opportunity to answer"),
			0
		)
	);

	TSharedPtr<FDialogueGraphNewNodeAction> newResponseNodeAction (
		new FDialogueGraphNewNodeAction (
			UDialogueGraphResponseNode::StaticClass(),
			FText::FromString("Nodes"),
			FText::FromString("ResponseNode"),
			FText::FromString("Makes a node with player answer variant"),
			0
		)
	);

	TSharedPtr<FDialogueGraphNewNodeAction> newInvokeNodeAction (
		new FDialogueGraphNewNodeAction (
			UDialogueGraphInvokeNode::StaticClass(),
			FText::FromString("Nodes"),
			FText::FromString("InvokeNode"),
			FText::FromString("Makes a node to invoke event"),
			0
		)
	);
	
	contextMenuBuilder.AddAction(newQuoteNodeAction);
	contextMenuBuilder.AddAction(newEndNodeAction);
	contextMenuBuilder.AddAction(newRequestNodeAction);
	contextMenuBuilder.AddAction(newResponseNodeAction);
	contextMenuBuilder.AddAction(newInvokeNodeAction);
}

const FPinConnectionResponse UDialogueGraphSchema::CanCreateConnection(const UEdGraphPin* sourcePin, const UEdGraphPin* targetPin) const
{
	 if(sourcePin == nullptr || targetPin == nullptr)
	 {
	 	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT("Temporary connection for visualization"));
	 }

	if(sourcePin->Direction == targetPin->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
	}

	if(sourcePin->Direction != EGPD_Output)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT(""));
}

void UDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& graph) const
{
	UDialogueGraphStartNode* startNode = NewObject<UDialogueGraphStartNode>(&graph);
	startNode->CreateNewGuid();
	startNode->NodePosX = -175;
	startNode->NodePosY = 0;
	UEdGraphPin* startNodeOutPin = startNode->CreateDefaultOutputPin();

	UDialogueGraphQuoteNode* quoteNode = NewObject<UDialogueGraphQuoteNode>(&graph);
	quoteNode->CreateNewGuid();
	quoteNode->NodePosX = 0;
	quoteNode->NodePosY = 0;
	UEdGraphPin* quoteNodeInPin = quoteNode->CreateDefaultInputPin();
	UEdGraphPin* quoteNodeOutPin = quoteNode->CreateDefaultOutputPin();
	
	UDialogueGraphEndNode* endNode = NewObject<UDialogueGraphEndNode>(&graph);
	endNode->CreateNewGuid();
	endNode->NodePosX = 250;
	endNode->NodePosY = 0;
	UEdGraphPin* endNodeInPin = endNode->CreateDefaultInputPin();

	startNode->InitNodeInfo(startNode);
	quoteNode->InitNodeInfo(quoteNode);
	endNode->InitNodeInfo(endNode);

	
	graph.AddNode(startNode);
	graph.AddNode(quoteNode);
	graph.AddNode(endNode);
	graph.Modify();

	TryCreateConnection(startNodeOutPin, quoteNodeInPin);
	TryCreateConnection(quoteNodeOutPin, endNodeInPin);
}

void UDialogueGraphSchema::OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2D& GraphPosition) const
{	
	/*UEdGraph* Graph = PinA->GetOwningNode()->GetGraph();

	UK2Node_Knot* RerouteNode = NewObject<UK2Node_Knot>(Graph);
	Graph->AddNode(RerouteNode);

	RerouteNode->NodePosX = GraphPosition.X;
	RerouteNode->NodePosY = GraphPosition.Y;

	RerouteNode->AllocateDefaultPins();

	UEdGraphPin* RerouteInputPin = RerouteNode->GetInputPin();
	UEdGraphPin* RerouteOutputPin = RerouteNode->GetOutputPin();

	if (RerouteInputPin && RerouteOutputPin)
	{
		PinA->BreakLinkTo(PinB);

		PinA->MakeLinkTo(RerouteInputPin);
		RerouteOutputPin->MakeLinkTo(PinB);
	}
	
	Graph->NotifyGraphChanged();
	Graph->Modify();*/
}


UEdGraphNode* FDialogueGraphNewNodeAction::PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2d location, bool bSelectNewNode)
{
	UDialogueGraphNodeBase* result = NewObject<UDialogueGraphNodeBase>(parentGraph, _classTemplate);
	result->CreateNewGuid();
	result->NodePosX = location.X;
	result->NodePosY = location.Y;

	result->InitNodeInfo(result);

	UEdGraphPin* inputPin = result->CreateDefaultInputPin();
	result->CreateDefaultOutputPin();

	if(inputPin != nullptr && fromPin != nullptr)
	{
		result->GetSchema()->TryCreateConnection(fromPin, inputPin);
	}
	
	parentGraph->AddNode(result, true, bSelectNewNode);
	parentGraph->Modify();

	return result;
}

