// Fill out your copyright notice in the Description page of Project Settings.


#include "Installers/HUDInstaller.h"

#include "Framework/DependencyInjection/DependencyContainer.h"
#include "HUD/GameplayHUD.h"

AHUDInstaller::AHUDInstaller()
{
}

void AHUDInstaller::InstallBindings(UDependencyContainer* Container)
{
	Super::InstallBindings(Container);

	UE_LOG(LogTemp,Error,TEXT("Inject character"));
	
	HUD = GetWorld()->SpawnActor<AGameplayHUD>(HUDClass);
	check(HUD);
	
	Container->Bind<AGameplayHUD>()->FromInstance(HUD);
}

void AHUDInstaller::Inject(UDependencyContainer* Container)
{
	Container->Resolve<APlayerController>()->MyHUD = HUD;
}
