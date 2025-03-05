#include "Nodes/DialogueGraphEndNode.h"

#include "App/DialogueGraphApp.h"

UEdGraphPin* UDialogueGraphEndNode::CreateGraphPin(EEdGraphPinDirection direction, FName name)
{
	if(direction == EGPD_Output)
	{
		UE_LOG(DialogueGraph, Error, TEXT("DialogueGraphEndNode::CreateGraphPin: Output direction not supported"));
		return nullptr;
	}
	
	FName category = TEXT("Inputs");
	FName subCategory = TEXT("DialogueGraphEndNodePin");

	UEdGraphPin* pin = CreatePin (
	direction,
	category,
	name
	);
	pin->PinType.PinSubCategory = subCategory;

	return pin;
}
