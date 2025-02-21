#include "Nodes/DialogueGraphNodeBase.h"

void UDialogueGraphNodeBase::GetNodeContextMenuActions(UToolMenu* menu, UGraphNodeContextMenuContext* context) const
{
	Super::GetNodeContextMenuActions(menu, context);

	FToolMenuSection& section  = menu->AddSection(TEXT("Main"), FText::FromString(TEXT("Node Actions")));
	UDialogueGraphNodeBase* node = (UDialogueGraphNodeBase*)this;
	
	if(CanUserDeleteNode())
	{
		section.AddMenuEntry (
		TEXT("DeleteNodeEntry"),
		FText::FromString(TEXT("Delete node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueGraphStyle"), TEXT("DialogueGraph.DeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateLambda (
			[node] {
				node->GetGraph()->RemoveNode(node);
			}
		)));
	}
}

void UDialogueGraphNodeBase::CreateDefaultPins(FName inputName, FName outputName)
{
	CreateDefaultInputPin(inputName);
	CreateDefaultOutputPin(outputName);
}

UEdGraphPin* UDialogueGraphNodeBase::CreateDefaultInputPin(FName name)
{
	return CreateGraphPin(EGPD_Input, name == "" ? TEXT("In") : name);
}

UEdGraphPin* UDialogueGraphNodeBase::CreateDefaultOutputPin(FName name)
{
	return CreateGraphPin(EGPD_Output, name == "" ? TEXT("Out") : name);
}
