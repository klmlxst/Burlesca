#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "NodeInfo/DialogueGraphResponseNodeInfo.h"
#include "DialogueGraphResponseNode.generated.h"

UCLASS()
class UDialogueGraphResponseNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public:
	// node interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titleType) const override { return FText::FromString("Response"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(0.9f, 0.3f, 0); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual bool CanDuplicateNode() const override { return true; }

	// _base interface
	virtual UEdGraphPin* CreateGraphPin(EEdGraphPinDirection direction, FName name) override;

	//node info
	virtual void InitNodeInfo(UObject* output) override { _nodeInfo = NewObject<UDialogueGraphResponseNodeInfo>(output); }
	virtual void SetNodeInfo(UDialogueGraphNodeInfo_Base* nodeInfo) override { _nodeInfo = Cast<UDialogueGraphResponseNodeInfo>(nodeInfo); }
	virtual UDialogueGraphNodeInfo_Base* GetNodeInfo() override { return _nodeInfo; }
	virtual UDialogueGraphResponseNodeInfo* GetSpecificNodeInfo() { return _nodeInfo; }
	virtual EDialogueGraphNodeType GetDialogueNodeType() const override { return EDialogueGraphNodeType::ResponseNode; }
	
protected:
	UPROPERTY()
	UDialogueGraphResponseNodeInfo* _nodeInfo;
};