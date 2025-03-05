#include "Nodes/DialogueGraphResponseNode.h"

UEdGraphPin* UDialogueGraphResponseNode::CreateGraphPin(EEdGraphPinDirection direction, FName name)
{
	FName category = (direction == EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName subCategory = TEXT("DialogueGraphResponseNodePin");

	UEdGraphPin* pin = CreatePin (
		direction,
		category,
		name
	);
	pin->PinType.PinSubCategory = subCategory;

	return pin;
}
