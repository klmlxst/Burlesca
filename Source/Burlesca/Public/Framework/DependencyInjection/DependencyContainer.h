// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DIHelpersClasses.h"
#include "DependencyContainer.generated.h"

BURLESCA_API DECLARE_LOG_CATEGORY_EXTERN(DependencyInjection, All, All);

class UFromBinder;

UCLASS()
class BURLESCA_API UDependencyContainer : public UObject
{
	GENERATED_BODY()

public:
	
	/**
	 * Use this function to bind an object to container.
	 * 
	 * @tparam T Binding class
	 */
	template <typename T>
	UFromBinder* Bind()
	{
		UFromBinder* FromBinder = NewObject<UFromBinder>(this);
		FromBinder->Init<T>(this);
		return FromBinder;
	}

	/**
	 * @brief Use this function to resolve object from container by his class or interface it implements.
	 * @tparam T Resolving object type.
	 * @return Returns resolved object pointer if found in container.
	 * @return Else return nullptr.
	 */
	template <typename T>
	T* Resolve()
	{
		if (UObject** FoundInstance = RegisteredInstances.Find(T::StaticClass()))
		{
			return Cast<T>(*FoundInstance);
		}

		UE_LOG(DependencyInjection, Warning, TEXT("No instance registered for class type %s."), *T::StaticClass()->GetName());
		return nullptr;
	}

	void Register(UClass* ClassName, UObject* Object);

private:
	UPROPERTY()
	TMap<UClass*, UObject*> RegisteredInstances;
};
