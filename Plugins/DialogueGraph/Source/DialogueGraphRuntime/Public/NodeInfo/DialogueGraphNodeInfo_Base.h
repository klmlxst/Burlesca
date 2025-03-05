#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeInfo_Base.generated.h"

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphNodeInfo_Base : public UObject
{
	GENERATED_BODY()

public:
	int GetNodeId() { return _nodeId; }
	void SetNodeId(int nodeId) { _nodeId = nodeId; }

	int GetDelayTime() { return _delayTime; }
	void SetDelayTime(int delayTime) { _delayTime = delayTime; }
protected:
	UPROPERTY(VisibleAnywhere)
	int _nodeId = 0;

	UPROPERTY(EditAnywhere)
	int _delayTime = -1; // -1 to use default
};