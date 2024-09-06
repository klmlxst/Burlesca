// Fill out your copyright notice in the Description page of Project Settings.


#include "Installers/MainSceneInstaller.h"

#include "BurlescaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Framework/EscapeButtonController.h"
#include "Framework/SignalBus.h"
#include "MainCharacter.h"
#include "MusicianInstruments/GuitarSetupController.h"
#include "Framework/DependencyInjection/DependencyContainer.h"
#include "Framework/DependencyInjection/DIHelpersClasses.h"
#include "MobilePhone/MobilePhoneController.h"
#include "Settings/SettingsContainer.h"

class AMobilePhone;


void AMainSceneInstaller::InstallBindings(UDependencyContainer* Container)
{
	if(Container)
	{
		PlayerController = GetWorld()->GetFirstPlayerController<ABurlescaPlayerController>();
		
		Container->Bind<APlayerController>()->FromInstance(PlayerController);
		Container->Bind<ABurlescaPlayerController>()->FromInstance(PlayerController);

		SignalBus = NewObject<USignalBus>(this);
		EscapeButtonController =  NewObject<UEscapeButtonController>(this);
		SettingsContainer = NewObject<USettingsContainer>(this);
		MobilePhoneController = NewObject<UMobilePhoneController>(this);
		
		Container->Bind<USignalBus>()->FromInstance(SignalBus);
		Container->Bind<UEscapeButtonController>()->FromInstance(EscapeButtonController);
		Container->Bind<USettingsContainer>()->FromInstance(SettingsContainer);
		Container->Bind<UMobilePhoneController>()->FromInstance(MobilePhoneController);
	}
}

void AMainSceneInstaller::Start(UDependencyContainer* Container)
{
	Super::Start(Container);

	MainCharacter = Container->Resolve<AMainCharacter>();
	MobilePhone = MainCharacter->GetMobilePhone();
	check(MobilePhone);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext,1);
	PlayerController->Init(SignalBus);
	
	EscapeButtonController->Init(SignalBus, EscapeButtonPressedAction, MainCharacter, PlayerController);
	EscapeButtonController->InitServicies(Container->Resolve<UGuitarSetupController>());

	MobilePhoneController->Init(MobilePhone, MainCharacter);
	MobilePhoneController->InitInputActions(TakePhoneInOrOutOfHandsAction);
}

void AMainSceneInstaller::SetupInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	EscapeButtonController->SetupInput(EnhancedInputComponent);
	MobilePhoneController->SetupInput(EnhancedInputComponent);
}
