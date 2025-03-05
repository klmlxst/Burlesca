#include "Nodes/DialogueGraphQuoteNode.h"

#include "NodeInfo/DialogueGraphQuoteNodeInfo.h"

UEdGraphPin* UDialogueGraphQuoteNode::CreateGraphPin(EEdGraphPinDirection direction, FName name)
{
	FName category = (direction == EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName subCategory = TEXT("DialogueGraphQuoteNodePin");

	UEdGraphPin* pin = CreatePin (
		direction,
		category,
		name
	);
	pin->PinType.PinSubCategory = subCategory;

	return pin;
}
