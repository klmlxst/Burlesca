// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacterComponents/TP_MainCharacterCameraController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "EventContainers/CharacterEventsContainer.h"
#include "Framework/SignalBus.h"
#include "GameFramework/Character.h"
#include "Settings/InputSettingsContainer.h"

UTP_MainCharacterCameraController::UTP_MainCharacterCameraController()
{
	
}

void UTP_MainCharacterCameraController::Init(UCameraComponent* camera, USignalBus* signalBus,
	UInputSettingsContainer* inputSettingsContainer)
{
	MainCamera = camera;
	SignalBus = signalBus;
	InputSettingsContainer = inputSettingsContainer;
}

void UTP_MainCharacterCameraController::SetupInput(UEnhancedInputComponent* input)
{
	Owner = Cast<ACharacter>(GetOwner());
	check(Owner);
	
	input->BindAction(LookXAction, ETriggerEvent::Triggered, this, &UTP_MainCharacterCameraController::LookRight);
	input->BindAction(LookYAction, ETriggerEvent::Triggered, this, &UTP_MainCharacterCameraController::LookUp);
}

void UTP_MainCharacterCameraController::PlayService()
{
	bIsServiceStoped = false;
}

void UTP_MainCharacterCameraController::StopService()
{
	bIsServiceStoped = true;
}

void UTP_MainCharacterCameraController::MoveCameraTo(AActor* PositionActor, float MovementDuration, bool bIsCameraMovingFromCharacter, bool bIsMovingToCharacter)
{
	if(PositionActor && MovementDuration != 0)
	{
		MoveCameraTo(PositionActor->GetActorLocation(), PositionActor->GetActorRotation(), MovementDuration, bIsCameraMovingFromCharacter);
	}
}

void UTP_MainCharacterCameraController::MoveCameraTo(FVector PositionVector, FRotator RotationVector, float MovementDuration, bool bIsCameraMovingFromCharacter, bool bIsMovingToCharacter)
{
	bIsCameraMovingToCharacter = false;
	
	if(GetWorld()->GetTimerManager().TimerExists(CameraMovementTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(CameraMovementTimerHandle);
	}
	
	if(bIsCameraMovingFromCharacter)
	{
		OnPlayerCameraPosition = MainCamera->GetComponentLocation();
		OnPlayerCameraRotator = MainCamera->GetComponentRotation();
		
		SignalBus->GetCharacterEventsContainer()->OnCharacterCameraMovedOutFromCharacter.Broadcast();
		bIsCameraOnCharacter = false;
	}

	bIsCameraMovingToCharacter = bIsMovingToCharacter;
	
	StartCameraPosition = MainCamera->GetComponentLocation();
	StartCameraRotation = MainCamera->GetComponentRotation();

	TargetCameraPosition = PositionVector;
	TargetCameraRotation = RotationVector;

	LerpSpeed = 1.0f/MovementDuration;
	TimeElapsed = 0.0f;
	
	GetWorld()->GetTimerManager().SetTimer(CameraMovementTimerHandle, this,
		&UTP_MainCharacterCameraController::UpdateCameraPosition, 0.01f, true);
}

void UTP_MainCharacterCameraController::ReturnCameraToCharacter(float MovementDuration)
{
	if(!bIsCameraOnCharacter && !bIsCameraMovingToCharacter)
	{
		MoveCameraTo(OnPlayerCameraPosition, OnPlayerCameraRotator, MovementDuration, false, true);
	}
}

void UTP_MainCharacterCameraController::UpdateCameraPosition()
{	
	TimeElapsed += 0.01f;
	float Delta = FMath::Clamp(TimeElapsed * LerpSpeed, 0.0f, 1.0f);
	
	FVector NewLocation = FMath::Lerp(StartCameraPosition, TargetCameraPosition, Delta);
	FRotator NewRotation = FMath::Lerp(StartCameraRotation, TargetCameraRotation, Delta);

	MainCamera->SetWorldLocation(NewLocation);
	MainCamera->SetWorldRotation(NewRotation);
	
	if(Delta >= 1)
	{
		SignalBus->GetCharacterEventsContainer()->OnCharacterCameraEndMovement.Broadcast();
		if(bIsCameraMovingToCharacter)
		{
			SignalBus->GetCharacterEventsContainer()->OnCharacterCameraReturnedToCharacter.Broadcast();
			bIsCameraOnCharacter = true;
		}
		GetWorld()->GetTimerManager().ClearTimer(CameraMovementTimerHandle);
		bIsCameraMovingToCharacter = false;
	}
}

void UTP_MainCharacterCameraController::LookUp(const FInputActionValue& Value)
{
	FRotator rotation = MainCamera->GetRelativeRotation();
	
	if(MainCamera->GetRelativeRotation().Pitch + Value.Get<float>() * InputSettingsContainer->GetMouseSensitivity() < 90 &&
		MainCamera->GetRelativeRotation().Pitch + Value.Get<float>() * InputSettingsContainer->GetMouseSensitivity() > -80 )
	{
		rotation =  MainCamera->GetRelativeRotation() + FRotator(Value.Get<float>() * InputSettingsContainer->GetMouseSensitivity(), 0.0f, 0.0f);
	}
	
	if(!bIsServiceStoped)
	{
		switch(InputSettingsContainer->bIsMouseInvertedY)
		{
			case true:
				MainCamera->SetRelativeRotation(rotation * -1);
				break;
			
			case false:
				MainCamera->SetRelativeRotation(rotation);
				break;
		}
	}
}

void UTP_MainCharacterCameraController::LookRight(const FInputActionValue& Value)
{
	if(!bIsServiceStoped)
	{
		switch(InputSettingsContainer->bIsMouseInvertedX)
		{
		case true:
			Owner->AddActorLocalRotation(FRotator(0.0f, -Value.Get<float>() * InputSettingsContainer->GetMouseSensitivity(), 0.0f));
			break;
			
		case false:
			Owner->AddActorLocalRotation(FRotator(0.0f,Value.Get<float>() * InputSettingsContainer->GetMouseSensitivity(), 0.0f));
			break;
		}
	}
}
