#pragma once

#include "CoreMinimal.h"
#include "NodeInfo/DialogueGraphNodeInfo_Base.h"
#include "NodeInfo/DialogueGraphNodeType.h"
#include "DialogueGraphNodeBase.generated.h"

class UDialogueGraphNodeInfo_Base;
class UDialogueGraphQuoteNodeInfo;

UCLASS()
class UDialogueGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:
	// node interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titleType) const override { return FText::FromString("Node"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor::Blue; }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual bool CanDuplicateNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* menu, UGraphNodeContextMenuContext* context) const override;

	// _base interface
	virtual UEdGraphPin* CreateGraphPin(EEdGraphPinDirection direction, FName name) { /* must be overriden */ return nullptr; }
	virtual void CreateDefaultPins(FName inputName = TEXT(""), FName outputName = TEXT(""));
	virtual UEdGraphPin* CreateDefaultInputPin(FName name = TEXT(""));
	virtual UEdGraphPin* CreateDefaultOutputPin(FName name = TEXT(""));
	
	// node info
	virtual void InitNodeInfo(UObject* output) { /* Nothing by default */ }
	virtual void SetNodeInfo(UDialogueGraphNodeInfo_Base* nodeInfo) { /* None by default */ }
	virtual UDialogueGraphNodeInfo_Base* GetNodeInfo() { /* None by default */ return nullptr; }
	virtual void SetInfoNodeId(uint64 id) { GetNodeInfo()->SetNodeId(id); }
	
	virtual EDialogueGraphNodeType GetDialogueNodeType() const { return EDialogueGraphNodeType::Unknown; }
	virtual void OnPropertiesChanged() { /* Nothing by default */ }
};