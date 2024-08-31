// Fill out your copyright notice in the Description page of Project Settings.


#include "Installers/MusicianInstrumentInstaller.h"

#include "Framework/DependencyInjection/DependencyContainer.h"
#include "MainCharacter.h"
#include "Framework/SignalBus.h"
#include "MusicianInstruments/GuitarSetupController.h"

void AMusicianInstrumentInstaller::InstallBindings(UDependencyContainer* Container)
{
	Super::InstallBindings(Container);

	/*  ---  Controller Creation  ---  */
	
	GuitarSetupController = NewObject<UGuitarSetupController>(this);
	check(GuitarSetupController);
	
	Container->Bind<UGuitarSetupController>()->FromInstance(GuitarSetupController);

	/*  ---  Controller Setup  ---  */

	GuitarSetupController->Init(Container->Resolve<AMainCharacter>(), Container->Resolve<USignalBus>());
	GuitarSetupController->InitGuitarSetup(GuitarSetupViewPlaceholder, LeftLight, RightLight, TuningPegs);
	GuitarSetupController->InitInputActions(SwitchPegAction, RotatePegAction, PlayStringAction);
}

void AMusicianInstrumentInstaller::SetupInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	GuitarSetupController->SetupInput(EnhancedInputComponent);
}
