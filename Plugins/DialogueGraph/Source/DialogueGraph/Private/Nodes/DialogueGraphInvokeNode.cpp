#include "Nodes/DialogueGraphInvokeNode.h"

UEdGraphPin* UDialogueGraphInvokeNode::CreateGraphPin(EEdGraphPinDirection direction, FName name)
{
	FName category = (direction == EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName subCategory = TEXT("DialogueGraphInvokeNodePin");

	UEdGraphPin* pin = CreatePin (
		direction,
		category,
		name
	);
	pin->PinType.PinSubCategory = subCategory;

	return pin;
}
