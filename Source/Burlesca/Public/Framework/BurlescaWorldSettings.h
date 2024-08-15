// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "BurlescaWorldSettings.generated.h"

class ASceneContext;
class UDependencyContainer;
/**
 * 
 */
UCLASS()
class BURLESCA_API ABurlescaWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	UDependencyContainer* GetDIContainer();
	
private:
	UPROPERTY(EditAnywhere, Category="Dependency Injection")
	ASceneContext* SceneContext;
	
};
