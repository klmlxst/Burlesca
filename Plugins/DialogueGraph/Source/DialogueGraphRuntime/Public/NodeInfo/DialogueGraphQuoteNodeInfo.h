#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeInfo_Base.h"
#include "DialogueGraphQuoteNodeInfo.generated.h"

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphQuoteNodeInfo : public UDialogueGraphNodeInfo_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText DialogueText;
};
	