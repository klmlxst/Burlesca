// Copyright Uncertain Studios (c). All Rights Reserved.

#include "Framework/DependencyInjection/SceneContext.h"
#include "Framework/DependencyInjection/DependencyContainer.h"
#include "Framework/DependencyInjection/InjectionInstaller.h"


ASceneContext::ASceneContext(): DIContainer(nullptr)
{
	
}

void ASceneContext::InitDiContainer()
{
	UE_LOG(LogTemp, Error, TEXT("InitDiContainer"));
	
	DIContainer = NewObject<UDependencyContainer>(this);
	check(DIContainer);

	Algo::SortBy(SceneInstallers, &AInjectionInstaller::InitializationOrder);
	
	for (AInjectionInstaller* Installer : SceneInstallers)
	{
		Installer->InstallBindings(DIContainer);
	}
}

void ASceneContext::StartInstallers()
{
	for (AInjectionInstaller* Installer : SceneInstallers)
	{
		Installer->Start(DIContainer);
	}
}

UDependencyContainer* ASceneContext::GetDIContainer() const
{
	return DIContainer;
}
