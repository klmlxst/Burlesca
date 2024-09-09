// Fill out your copyright notice in the Description page of Project Settings.


#include "Installers/MainCharacterInstaller.h"

#include "MainCharacter.h"
#include "MainCharacterAnimInstance.h"
#include "Framework/SignalBus.h"
#include "Framework/DependencyInjection/DependencyContainer.h"
#include "Framework/DependencyInjection/DIHelpersClasses.h"


AMainCharacterInstaller::AMainCharacterInstaller()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainCharacterInstaller::InstallBindings(UDependencyContainer* Container)
{
	Super::InstallBindings(Container);

	UE_LOG(LogTemp, Error, TEXT("Character Installer Install Bindings"));
	
	if (CharacterClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			MainCharacter = World->SpawnActor<AMainCharacter>(CharacterClass, CharacterSpawnPosition, CharacterSpawnRotation, SpawnParams);
		}	
	}

	MainCharacterAnimInstance = MainCharacter->CreateAnimInstance(AnimInstanceClass);

	Container->Bind<AMainCharacter>()->FromInstance(MainCharacter);
	Container->Bind<UMainCharacterAnimInstance>()->FromInstance(MainCharacterAnimInstance);
}

void AMainCharacterInstaller::Start(UDependencyContainer* Container)
{
	Super::Start(Container);

	MainCharacterAnimInstance->Init(Container->Resolve<USignalBus>());
}
