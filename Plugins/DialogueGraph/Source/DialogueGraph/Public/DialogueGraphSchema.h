#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphSchema.generated.h"

UCLASS()
class UDialogueGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* sourcePin, const UEdGraphPin* targetPin) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& graph) const override;
	virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2D& GraphPosition) const override;
};

USTRUCT()
struct FDialogueGraphNewNodeAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()

public:
	FDialogueGraphNewNodeAction() {}
	FDialogueGraphNewNodeAction(UClass* classTemplate, const FText& inNodeCategory, FText inMenuDesc, FText inToolTip, const int32 inGrouping)
		: FEdGraphSchemaAction(inNodeCategory, inMenuDesc, inToolTip, inGrouping), _classTemplate(classTemplate) {}

	//  --  called when clicked create node
	virtual UEdGraphNode* PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2d location, bool bSelectNewNode = true) override;

protected:
	UClass* _classTemplate = nullptr;
};