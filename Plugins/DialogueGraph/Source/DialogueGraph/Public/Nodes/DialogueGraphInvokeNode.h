#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "NodeInfo/DialogueGraphInvokeNodeInfo.h"
#include "DialogueGraphInvokeNode.generated.h"

UCLASS()
class UDialogueGraphInvokeNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public:
	// node interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titleType) const override { return FText::FromString("Invoke"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor::Yellow; }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual bool CanDuplicateNode() const override { return true; }

	// _base interface
	virtual UEdGraphPin* CreateGraphPin(EEdGraphPinDirection direction, FName name) override;

	//node info
	virtual void InitNodeInfo(UObject* output) override { _nodeInfo = NewObject<UDialogueGraphInvokeNodeInfo>(output); }
	virtual void SetNodeInfo(UDialogueGraphNodeInfo_Base* nodeInfo) override { _nodeInfo = Cast<UDialogueGraphInvokeNodeInfo>(nodeInfo); }
	virtual UDialogueGraphNodeInfo_Base* GetNodeInfo() override { return _nodeInfo; }
	virtual UDialogueGraphInvokeNodeInfo* GetSpecificNodeInfo() { return _nodeInfo; }
	virtual EDialogueGraphNodeType GetDialogueNodeType() const override { return EDialogueGraphNodeType::InvokeNode; }
	
protected:
	UPROPERTY()
	UDialogueGraphInvokeNodeInfo* _nodeInfo;
};