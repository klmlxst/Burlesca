// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/DependencyInjection/DependencyContainer.h"
#include "Framework/DependencyInjection/DIHelpersClasses.h"

DEFINE_LOG_CATEGORY(DependencyInjection);


void UDependencyContainer::Register(UClass* ClassName, UObject* Object)
{
	if (RegisteredInstances.Contains(ClassName))
	{
		UE_LOG(DependencyInjection, Log, TEXT("Class type %s is already registered. Overwriting existing instance."), *ClassName->GetName());
	}
		
	RegisteredInstances.Add(ClassName, Object);
}
