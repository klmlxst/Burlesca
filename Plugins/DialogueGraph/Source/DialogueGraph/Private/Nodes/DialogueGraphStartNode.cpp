#include "Nodes/DialogueGraphStartNode.h"

#include "App/DialogueGraphApp.h"

UEdGraphPin* UDialogueGraphStartNode::CreateGraphPin(EEdGraphPinDirection direction, FName name)
{
	if(direction == EGPD_Input)
	{
		UE_LOG(DialogueGraph, Error, TEXT("DialogueGraphStartNode::CreateGraphPin: Input direction not supported"));
		return nullptr;
	}
	
	FName category = TEXT("Outputs");
	FName subCategory = TEXT("DialogueGraphStartNodePin");
	UEdGraphPin* pin = CreatePin (
		direction,
		category,
		name
	);
	pin->PinType.PinSubCategory = subCategory;
	return pin;
	
}
