#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "NodeInfo/DialogueGraphRequestNodeInfo.h"
#include "DialogueGraphRequestNode.generated.h"

UCLASS()
class UDialogueGraphRequestNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public:
	// node interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titleType) const override { return FText::FromString("Request"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(1, 0.3f, 0.1f); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual bool CanDuplicateNode() const override { return true; }
	virtual void GetNodeContextMenuActions(UToolMenu* menu, UGraphNodeContextMenuContext* context) const override;

	// _base interface
	virtual UEdGraphPin* CreateGraphPin(EEdGraphPinDirection direction, FName name) override;
	virtual UEdGraphPin* CreateDefaultOutputPin(FName name = TEXT("")) override { return Super::CreateDefaultOutputPin(TEXT("Response")); }

	//node info
	virtual void InitNodeInfo(UObject* output) override { _nodeInfo = NewObject<UDialogueGraphRequestNodeInfo>(output); }
	virtual void SetNodeInfo(UDialogueGraphNodeInfo_Base* nodeInfo) override { _nodeInfo = Cast<UDialogueGraphRequestNodeInfo>(nodeInfo); }
	virtual UDialogueGraphNodeInfo_Base* GetNodeInfo() override { return _nodeInfo; }
	virtual UDialogueGraphRequestNodeInfo* GetSpecificNodeInfo() { return _nodeInfo; }
	virtual EDialogueGraphNodeType GetDialogueNodeType() const override { return EDialogueGraphNodeType::RequestNode; }
	
protected:
	UPROPERTY()
	UDialogueGraphRequestNodeInfo* _nodeInfo;
};