// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InjectionInstaller.generated.h"

class UDependencyContainer;

UCLASS(Abstract)
class BURLESCA_API AInjectionInstaller : public AActor
{
	GENERATED_BODY()
	
public:	
	AInjectionInstaller();
	
	virtual void InstallBindings(UDependencyContainer* Container);
	virtual void Start(UDependencyContainer* Container);

	UPROPERTY(EditInstanceOnly)
	uint8 InitializationOrder = 10;
};
