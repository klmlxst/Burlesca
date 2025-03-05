// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConditionsRegistry/Condition.h"
#include "Framework/DependencyInjection/DependencyContainer.h"
#include "MusicianInstruments/GuitarSetupController.h"
#include "UObject/Object.h"
#include "GuitarSetupCondition.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UGuitarSetupCondition : public UObject, public ICondition
{
	GENERATED_BODY()

public:
	virtual void InitDependenciesFromDIContainer(UDependencyContainer* container) override
	{
		GuitarSetupController = container->Resolve<UGuitarSetupController>();

		if(GuitarSetupController == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("UGuitarSetupResponseCondition::InitDependenciesFromDIContainer - GuitarSetupController is null"));
		}
	}
	
	virtual bool CheckCondition(FConditionParams params) override
	{
		return GuitarSetupController->GetIsGuitarSetupCompleted();
	}

protected:
	UPROPERTY()
	UGuitarSetupController* GuitarSetupController = nullptr;
};
