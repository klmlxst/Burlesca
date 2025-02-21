#pragma once

#include "CoreMinimal.h"
#include "NodeInfo/DialogueGraphNodeType.h"
#include "DialogueGraphRuntimeGraph.generated.h"

class UDialogueGraphNodeInfo_Base;

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
};

UCLASS()
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphRuntimeGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UDialogueGraphRuntimeNode*> Nodes;
};