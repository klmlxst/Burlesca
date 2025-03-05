// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionParams.h"
#include "ConditionType.h"
#include "Framework/DependencyInjection/Inject.h"
#include "UObject/Object.h"
#include "ConditionRegistry.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UConditionRegistry : public UObject, public IInject
{
	GENERATED_BODY()

public:
	void virtual Inject(UDependencyContainer* Container) override;
	bool CheckCondition(EConditionType conditionType, FConditionParams params);
	
	UPROPERTY()
	TMap<EConditionType, UObject*> Conditions;
};
