#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "NodeInfo/DialogueGraphEndNodeInfo.h"
#include "DialogueGraphEndNode.generated.h"

UCLASS()
class UDialogueGraphEndNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()
	
public:
	// node interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titleType) const override { return FText::FromString("End"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor::Red; }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual bool CanDuplicateNode() const override { return true; }

	// base interface
	virtual UEdGraphPin* CreateGraphPin(EEdGraphPinDirection direction, FName name) override;
	virtual void CreateDefaultPins(FName inputName = TEXT(""), FName outputName = TEXT("")) override { CreateDefaultInputPin(); }
	virtual UEdGraphPin* CreateDefaultInputPin(FName name = TEXT("")) override { return Super::CreateDefaultInputPin(TEXT("End")); }
	virtual UEdGraphPin* CreateDefaultOutputPin(FName name = TEXT("")) override { return nullptr; }

	//node info
	virtual void InitNodeInfo(UObject* output) override { _nodeInfo = NewObject<UDialogueGraphEndNodeInfo>(output); }
	virtual void SetNodeInfo(UDialogueGraphNodeInfo_Base* nodeInfo) override { _nodeInfo = Cast<UDialogueGraphEndNodeInfo>(nodeInfo); }
	virtual UDialogueGraphNodeInfo_Base* GetNodeInfo() override { return _nodeInfo; }
	virtual UDialogueGraphEndNodeInfo* GetSpecificNodeInfo() { return _nodeInfo; }
	virtual EDialogueGraphNodeType GetDialogueNodeType() const override { return EDialogueGraphNodeType::EndNode; }
	
protected:
	UPROPERTY()
	UDialogueGraphEndNodeInfo* _nodeInfo;
};