#include "Nodes/DialogueGraphRequestNode.h"

void UDialogueGraphRequestNode::GetNodeContextMenuActions(UToolMenu* menu, UGraphNodeContextMenuContext* context) const
{
	Super::GetNodeContextMenuActions(menu, context);
	
	FToolMenuSection& section  = *menu->FindSection(TEXT("Main"));
	UDialogueGraphRequestNode* node = (UDialogueGraphRequestNode*)this;
	
	section.AddMenuEntry (
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add pin to a node")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(TEXT("DialogueGraphStyle"), TEXT("DialogueGraph.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateLambda (
			[node] {
				node->CreateGraphPin(EGPD_Output, TEXT("Response")); 				
				
				node->GetGraph()->NotifyGraphChanged();
				node->GetGraph()->Modify();
			}
		))
	);

	section.AddMenuEntry (
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete pin from node")),
		FText::FromString(TEXT("Deletes the pin")),
		FSlateIcon(TEXT("DialogueGraphStyle"), TEXT("DialogueGraph.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateLambda (
			[node] {
				UEdGraphPin* pin = node->GetPinAt(node->Pins.Num() - 1);
				if(pin && pin->Direction != EGPD_Input)
				{
					node->RemovePin(pin);
					
					node->GetGraph()->NotifyGraphChanged();
					node->GetGraph()->Modify();	
				}				
			}
		))
	);
}

UEdGraphPin* UDialogueGraphRequestNode::CreateGraphPin(EEdGraphPinDirection direction, FName name)
{
	FName category = (direction == EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName subCategory = TEXT("DialogueGraphRequestNodePin");

	UEdGraphPin* pin = CreatePin (
		direction,
		category,
		name
	);
	pin->PinType.PinSubCategory = subCategory;

	return pin;
}
