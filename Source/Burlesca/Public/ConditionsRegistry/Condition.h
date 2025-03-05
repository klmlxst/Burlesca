// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionParams.h"
#include "Framework/DependencyInjection/DependencyContainer.h"
#include "UObject/Interface.h"
#include "Condition.generated.h"

UINTERFACE()
class UCondition : public UInterface
{
	GENERATED_BODY()
};

class BURLESCA_API ICondition
{
	GENERATED_BODY()

public:
	virtual bool CheckCondition(FConditionParams conditionParams) = 0;
	virtual void InitDependenciesFromDIContainer(UDependencyContainer* container) = 0;
};
