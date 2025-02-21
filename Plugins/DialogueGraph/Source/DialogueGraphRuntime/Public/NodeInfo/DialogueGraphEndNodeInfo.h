#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeInfo_Base.h"
#include "DialogueGraphEndNodeInfo.generated.h"

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphEndNodeInfo : public UDialogueGraphNodeInfo_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bBanCompanionInMessenger = false;

	UPROPERTY(EditAnywhere)
	bool bBanPlayerInMessenger = false;
};
