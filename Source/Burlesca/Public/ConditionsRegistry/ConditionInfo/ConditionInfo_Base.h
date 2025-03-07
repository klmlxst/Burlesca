#pragma once

#include "CoreMinimal.h"
#include "ConditionsRegistry/ConditionParams.h"
#include "ConditionInfo_Base.generated.h"

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class BURLESCA_API UConditionInfo_Base : public UObject
{
	GENERATED_BODY()

public:
	virtual FConditionParams GetConditionParams() { return FConditionParams(); }
};