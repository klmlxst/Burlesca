#pragma once

#include "CoreMinimal.h"
#include "DialogueInvocationParams.generated.h"

USTRUCT(BlueprintType)
struct FDialogueInvocationParams
{
	GENERATED_BODY()

public:
	FDialogueInvocationParams() {  }
	
	FDialogueInvocationParams (
		const FVariant& firstParam
	) : first(firstParam) { }
	
	FDialogueInvocationParams (
		const FVariant& firstParam,
		const FVariant& secondParam
	) : first(firstParam), second(secondParam) { }
	
	FDialogueInvocationParams (
		const FVariant& firstParam,
		const FVariant& secondParam,
		const FVariant& thirdParam
	) : first(firstParam), second(secondParam), third(thirdParam) { }
	
	FDialogueInvocationParams (
		const FVariant& firstParam,
		const FVariant& secondParam,
		const FVariant& thirdParam,
		const FVariant& fourthParam
	) : first(firstParam), second(secondParam), third(thirdParam), fourth(fourthParam) { }
	
	FDialogueInvocationParams (
		const FVariant& firstParam,
		const FVariant& secondParam,
		const FVariant& thirdParam,
		const FVariant& fourthParam,
		const FVariant& fifthParam
	) : first(firstParam), second(secondParam), third(thirdParam), fourth(fourthParam), fifth(fifthParam) { }
	
	FVariant first;
	FVariant second;
	FVariant third;
	FVariant fourth;
	FVariant fifth;
};