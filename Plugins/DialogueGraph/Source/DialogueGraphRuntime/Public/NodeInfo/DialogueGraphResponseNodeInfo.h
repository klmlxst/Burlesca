#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeInfo_Base.h"
#include "DialogueGraphResponseNodeInfo.generated.h"

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphResponseNodeInfo : public UDialogueGraphNodeInfo_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText ResponseText;

	UPROPERTY(EditAnywhere)
	bool bHasCondition;
	
	UPROPERTY(EditAnywhere)
	FText ConditionName;

	UPROPERTY(EditAnywhere)
	FText ConditionTooltip;	
};
	