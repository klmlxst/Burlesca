// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/DependencyInjection/DependencyContainer.h"


void UDependencyContainer::Register(UClass* ClassName, UObject* Object)
{
	if (RegisteredInstances.Contains(ClassName))
	{
		UE_LOG(LogTemp, Log, TEXT("Class type %s is already registered. Overwriting existing instance."), *ClassName->GetName());
	}
		
	RegisteredInstances.Add(ClassName, Object);
}
