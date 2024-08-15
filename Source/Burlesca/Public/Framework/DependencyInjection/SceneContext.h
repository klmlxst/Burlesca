// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneContext.generated.h"

class AInjectionInstaller;
class UDependencyContainer;

UCLASS()
class BURLESCA_API ASceneContext : public AActor
{
	GENERATED_BODY()
	
public:	
	ASceneContext();

	void InitDiContainer();
	UDependencyContainer* GetDIContainer() const;

private:
	UPROPERTY(EditAnywhere, Category = "Dependency Injection", meta = (AllowedClasses = "InjectionInstaller"))
	TArray<AInjectionInstaller*> SceneInstallers;

	virtual void PostInitProperties() override;

	UPROPERTY()
	UDependencyContainer* DIContainer;
};
