// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DependencyContainer.generated.h"

BURLESCA_API DECLARE_LOG_CATEGORY_EXTERN(DependencyInjection, All, All);

class UFromBinder;

UCLASS()
class BURLESCA_API UDependencyContainer : public UObject
{
	GENERATED_BODY()

public:
	template <typename T>
	UFromBinder* Bind();

	template <typename T>
	T* Resolve();

	void Register(UClass* ClassName, UObject* Object);

private:
	UPROPERTY()
	TMap<UClass*, UObject*> RegisteredInstances;
};
