#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueGraphStartNode.generated.h"

UCLASS()
class UDialogueGraphStartNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public:
	// node interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titleType) const override { return FText::FromString("Start"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor::Green; }
	virtual bool CanUserDeleteNode() const override { return false; }
	virtual bool CanDuplicateNode() const override { return false; }

	// base interface
	virtual UEdGraphPin* CreateGraphPin(EEdGraphPinDirection direction, FName name) override;
	virtual void CreateDefaultPins(FName inputName = TEXT(""), FName outputName = TEXT("")) override { CreateDefaultOutputPin(); }
	virtual UEdGraphPin* CreateDefaultInputPin(FName name = TEXT("")) override { return nullptr; }
	virtual UEdGraphPin* CreateDefaultOutputPin(FName name = TEXT("")) override { return Super::CreateDefaultOutputPin(TEXT("Start")); }

	//node info
	//node info
	virtual void InitNodeInfo(UObject* output) override { _nodeInfo = NewObject<UDialogueGraphNodeInfo_Base>(output); }
	virtual void SetNodeInfo(UDialogueGraphNodeInfo_Base* nodeInfo) override { _nodeInfo = Cast<UDialogueGraphNodeInfo_Base>(nodeInfo); }
	virtual UDialogueGraphNodeInfo_Base* GetNodeInfo() override { return _nodeInfo; }
	virtual EDialogueGraphNodeType GetDialogueNodeType() const override { return EDialogueGraphNodeType::StartNode; }

protected:
	UPROPERTY()
	UDialogueGraphNodeInfo_Base* _nodeInfo;
};