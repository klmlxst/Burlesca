// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/BurlescaWorldSettings.h"
#include "Framework/DependencyInjection/SceneContext.h"

UDependencyContainer* ABurlescaWorldSettings::GetDIContainer()
{
	check(SceneContext);
	return SceneContext->GetDIContainer();
}
