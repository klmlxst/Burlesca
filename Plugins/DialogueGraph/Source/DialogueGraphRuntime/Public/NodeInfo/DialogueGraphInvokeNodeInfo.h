#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeInfo_Base.h"
#include "DialogueGraphInvokeNodeInfo.generated.h"

UENUM()
enum class EInvokeNodeEventContainer
{
	Global,
	Character,
	Devices,
	MusicalInstruments
};

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphInvokeNodeInfo : public UDialogueGraphNodeInfo_Base
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere)
	EInvokeNodeEventContainer EventContainer;

	UPROPERTY(EditAnywhere)
	FName EventName;
};
	