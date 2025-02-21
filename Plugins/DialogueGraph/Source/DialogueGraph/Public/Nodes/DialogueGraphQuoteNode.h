#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "NodeInfo/DialogueGraphQuoteNodeInfo.h"
#include "DialogueGraphQuoteNode.generated.h"

class UDialogueGraphQuoteNodeInfo;

UCLASS()
class UDialogueGraphQuoteNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public:
	// node interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titleType) const override { return FText::FromString("Quote"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor::Blue; }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual bool CanDuplicateNode() const override { return true; }

	// _base interface
	virtual UEdGraphPin* CreateGraphPin(EEdGraphPinDirection direction, FName name) override;

	//node info
	virtual void InitNodeInfo(UObject* output) override { _nodeInfo = NewObject<UDialogueGraphQuoteNodeInfo>(output); }
	virtual void SetNodeInfo(UDialogueGraphNodeInfo_Base* nodeInfo) override { _nodeInfo = Cast<UDialogueGraphQuoteNodeInfo>(nodeInfo); }
	virtual UDialogueGraphNodeInfo_Base* GetNodeInfo() override { return _nodeInfo; }
	virtual UDialogueGraphQuoteNodeInfo* GetSpecificNodeInfo() { return _nodeInfo; }
	virtual EDialogueGraphNodeType GetDialogueNodeType() const override { return EDialogueGraphNodeType::QuoteNode; }
	
protected:
	UPROPERTY()
	UDialogueGraphQuoteNodeInfo* _nodeInfo;
};