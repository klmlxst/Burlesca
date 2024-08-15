// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/DependencyInjection/InjectionInstaller.h"
#include "MainSceneInstaller.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API AMainSceneInstaller : public AInjectionInstaller
{
	GENERATED_BODY()

public:
	virtual void InstallBindings(UDependencyContainer* Container) override;
};
