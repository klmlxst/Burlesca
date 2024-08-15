// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/DependencyInjection/DependencyContainer.h"
#include "Framework/DependencyInjection/DIHelpersClasses.h"

DEFINE_LOG_CATEGORY(DependencyInjection);

/**
 * Use this function to bind an object to container.
 * 
 * @tparam T Binding class
 */
template <typename T>
UFromBinder* UDependencyContainer::Bind()
{
	UFromBinder* FromBinder = NewObject<UFromBinder>(this);
	FromBinder->Init<T>(this, NewObject<UBindInfo>(this));
	return FromBinder;
}

/**
 * @brief Use this function to resolve object from container by his class or interface it implements.
 * @tparam T Resolving object type.
 * @return Returns resolved object pointer if found in container.
 * @return Else return nullptr.
 */
template <typename T>
T* UDependencyContainer::Resolve()
{
	if (UObject** FoundInstance = RegisteredInstances.Find(T::StaticClass))
	{
		return *FoundInstance;
	}

	UE_LOG(DependencyInjection, Warning, TEXT("No instance registered for class type %s."), *T::StaticClass->GetName());
	return nullptr;
}

void UDependencyContainer::Register(UClass* ClassName, UObject* Object)
{
	if (RegisteredInstances.Contains(ClassName))
	{
		UE_LOG(DependencyInjection, Log, TEXT("Class type %s is already registered. Overwriting existing instance."), *ClassName->GetName());
	}
		
	RegisteredInstances.Add(ClassName, Object);
}
