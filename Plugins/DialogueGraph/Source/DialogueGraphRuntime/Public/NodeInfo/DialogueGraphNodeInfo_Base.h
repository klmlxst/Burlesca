#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeInfo_Base.generated.h"

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphNodeInfo_Base : public UObject
{
	GENERATED_BODY()

public:
	uint64 GetNodeId();
	void SetNodeId(uint64 nodeId) { _nodeId = nodeId; }
	
protected:
	UPROPERTY(VisibleAnywhere)
	uint64 _nodeId = 0;
};