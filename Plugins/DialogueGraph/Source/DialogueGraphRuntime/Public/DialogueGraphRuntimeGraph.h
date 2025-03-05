#pragma once

#include "CoreMinimal.h"
#include "NodeInfo/DialogueGraphNodeInfo_Base.h"
#include "NodeInfo/DialogueGraphNodeType.h"
#include "DialogueGraphRuntimeGraph.generated.h"

class UDialogueGraphRuntimeNode;
class UDialogueGraphNodeInfo_Base;

DECLARE_LOG_CATEGORY_CLASS(DialogueGraphAsset, Log, All);

UCLASS()
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphRuntimePin : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName PinName;

	UPROPERTY()
	FGuid PinId;

	UPROPERTY()
	UDialogueGraphRuntimePin* Connection = nullptr;

	UPROPERTY()
	UDialogueGraphRuntimeNode* ParentNode = nullptr;
};

UCLASS()
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphRuntimeNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EDialogueGraphNodeType NodeType = EDialogueGraphNodeType::QuoteNode;
	
	UPROPERTY()
	UDialogueGraphRuntimePin* InputPin = nullptr;

	UPROPERTY()
	TArray<UDialogueGraphRuntimePin*> OutputPins;

	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	UDialogueGraphNodeInfo_Base* NodeInfo = nullptr;

	UDialogueGraphRuntimeNode* GetNextNode(int8 pinId = 0)
	{
		if(OutputPins[pinId] && OutputPins[pinId]->Connection)
		{
			if(!OutputPins[pinId]->Connection->ParentNode)
			{
				UE_LOG(DialogueGraphAsset, Error, TEXT("GetNextNode : No parent node"));
				return nullptr;
			}
			
			return OutputPins[pinId]->Connection->ParentNode;
		}
	
		UE_LOG(DialogueGraphAsset, Error, TEXT("GetNextNode : Output pin or its connection is nullptr"));
		
		return nullptr;
	}

	TArray<UDialogueGraphRuntimeNode*> GetAllNextNodes()
	{
		TArray<UDialogueGraphRuntimeNode*> result;
		
		for(UDialogueGraphRuntimePin* pin : OutputPins)
		{
			if(!pin || !pin->Connection)
			{
				break;
			}
			
			if(!pin->Connection->ParentNode)
			{
				UE_LOG(DialogueGraphAsset, Error, TEXT("GetNextNode : Output pin or its connection is nullptr"));
			}
			
			result.Add(pin->Connection->ParentNode);
		}

		return result;
	}
};

UCLASS()
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphRuntimeGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UDialogueGraphRuntimeNode*> Nodes;

	UPROPERTY()
	UDialogueGraphRuntimeNode* CurrentDialogueNode;
	
	UDialogueGraphRuntimeNode* GetNodeWithId(uint64 id)
	{
		for(UDialogueGraphRuntimeNode* node : Nodes)
		{
			if(node->NodeInfo->GetNodeId() == id)
				return node;
		}
		UE_LOG(DialogueGraphAsset, Error, TEXT("GetNodeWithId : No Node Found"));
		return nullptr;
	}

	void GoToNextNode()
	{
		CurrentDialogueNode = CurrentDialogueNode->GetNextNode();
		if(!CurrentDialogueNode)
			UE_LOG(DialogueGraphAsset, Error, TEXT("GoToNextNode : No next node"));
	}
};