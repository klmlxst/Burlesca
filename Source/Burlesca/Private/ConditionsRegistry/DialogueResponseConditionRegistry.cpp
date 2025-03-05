// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionsRegistry/ConditionRegistry.h"
#include "ConditionsRegistry/Conditions/GuitarSetupCondition.h"
#include "Dialogue/DialogueSystemManager.h"

void UConditionRegistry::Inject(UDependencyContainer* Container)
{
	UGuitarSetupCondition* guitarSetupResponseCondition = NewObject<UGuitarSetupCondition>(this);
	guitarSetupResponseCondition->InitDependenciesFromDIContainer(Container);
	Conditions.Add(EConditionType::IsGuitarSetUp, guitarSetupResponseCondition);
}

bool UConditionRegistry::CheckCondition(EConditionType conditionType, FConditionParams params)
{
	UObject** objPtr = Conditions.Find(conditionType);
	if(objPtr)
	{
		UObject* obj = *objPtr;
		if(obj)
		{
			ICondition* condition = Cast<ICondition>(obj);
			return condition->CheckCondition(params);
		}
	}
    
	UE_LOG(DialogueGraphRuntime, Error, TEXT("No condition with name: %d was found"), conditionType);
	return false;
}
