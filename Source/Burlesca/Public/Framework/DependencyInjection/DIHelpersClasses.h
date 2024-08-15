// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DependencyContainer.h"
#include "DIHelpersClasses.generated.h"

class UToBinder;
class UFromBinder;
class UDependencyContainer;

UCLASS()
class BURLESCA_API UBindInfo : public UObject
{
	GENERATED_BODY()

public:
	UBindInfo();
	
	UClass* FromBindClass;
	UClass* ToBindClass;

	UPROPERTY()
	UDependencyContainer* Container;
};



UCLASS()
class BURLESCA_API UFromBinder : public UObject
{
	GENERATED_BODY()

public:
	UFromBinder();
	
	template <typename T>
	void Init(UDependencyContainer* Container);
	
	UToBinder* FromNew() const;

	void FromInstance(UObject* Object) const;

private:
	UPROPERTY()
	UBindInfo* BindInfo;
	
};



UCLASS()
class BURLESCA_API UToBinder : public UObject
{
	GENERATED_BODY()

public:
	UToBinder();
	void Init(UBindInfo* bindInfo);
	
	template <typename T>
	void To();

private:

	UPROPERTY()
	UBindInfo* BindInfo;
};
