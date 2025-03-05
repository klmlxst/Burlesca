// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EscapeButtonController.h"

#include "BurlescaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "MusicianInstruments/GuitarSetupController.h"
#include "Framework/SignalBus.h"

void UEscapeButtonController::Init(USignalBus* signalBus, UInputAction* escapeButton, AMainCharacter* mainCharacter,
	ABurlescaPlayerController* playerController)
{
	EscapeButtonPressed = escapeButton;
	MainCharacter = mainCharacter;
	SignalBus = signalBus;
	PlayerController = playerController;

	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraReturnedToCharacter.AddDynamic(this, &UEscapeButtonController::SetIsCameraReturningToPlayerToFalse);
}

void UEscapeButtonController::InitServicies(UGuitarSetupController* guitarSetupController)
{
	GuitarSetupController = guitarSetupController;
}

void UEscapeButtonController::ProcessEscapeData()
{
	if(bIsCameraReturningToPlayer)
	{
		PlayerController->GetIsGamePaused()?PlayerController->UnpauseGame():PlayerController->PauseGame();
	}
	else if(GuitarSetupController->GetIsGuitarSetsUp())
	{
		GuitarSetupController->StopGuitarSetup();
		bIsCameraReturningToPlayer = true;
	}
	else
	{
		PlayerController->GetIsGamePaused()?PlayerController->UnpauseGame():PlayerController->PauseGame();
	}
}

void UEscapeButtonController::SetIsCameraReturningToPlayerToFalse()
{
	bIsCameraReturningToPlayer = false;
}

void UEscapeButtonController::SetupInput(UEnhancedInputComponent* InputComponent)
{
	FEnhancedInputActionEventBinding& Binding =  InputComponent->BindAction(EscapeButtonPressed, ETriggerEvent::Started, this, &UEscapeButtonController::ProcessEscapeData);
}
