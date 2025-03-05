#pragma once

#include "CoreMinimal.h"
#include "ConditionParams.generated.h"

USTRUCT(BlueprintType)
struct FConditionParams
{
	GENERATED_BODY()

public:
	FConditionParams() {  }
	
	FConditionParams (
		const FVariant& firstParam
	) : first(firstParam) { }
	
	FConditionParams (
		const FVariant& firstParam,
		const FVariant& secondParam
	) : first(firstParam), second(secondParam) { }
	
	FConditionParams (
		const FVariant& firstParam,
		const FVariant& secondParam,
		const FVariant& thirdParam
	) : first(firstParam), second(secondParam), third(thirdParam) { }
	
	FConditionParams (
		const FVariant& firstParam,
		const FVariant& secondParam,
		const FVariant& thirdParam,
		const FVariant& fourthParam
	) : first(firstParam), second(secondParam), third(thirdParam), fourth(fourthParam) { }
	
	FConditionParams (
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