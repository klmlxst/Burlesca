// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacterComponents/TP_MainCharacterCameraController.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

UTP_MainCharacterCameraController::UTP_MainCharacterCameraController()
{

}

void UTP_MainCharacterCameraController::Init(UCameraComponent* camera)
{
	MainCamera = camera;
}

void UTP_MainCharacterCameraController::SetupInput(UInputComponent* input)
{
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(input);
	
	enhancedInputComponent->BindAction(LookXAction, ETriggerEvent::Triggered, this, &UTP_MainCharacterCameraController::LookRight);
	enhancedInputComponent->BindAction(LookYAction, ETriggerEvent::Triggered, this, &UTP_MainCharacterCameraController::LookUp);
}

void UTP_MainCharacterCameraController::ChangePossesionState(bool targetState)
{
	IsPossesedByCutscene = targetState;
}

void UTP_MainCharacterCameraController::BeginPlay()
{
	Owner = Cast<ACharacter>(GetOwner());
	check(Owner);
}

void UTP_MainCharacterCameraController::LookUp(const FInputActionValue& Value)
{
	if(!IsPossesedByCutscene)
	{
		Owner->AddControllerPitchInput(-Value.Get<float>());
	}
}

void UTP_MainCharacterCameraController::LookRight(const FInputActionValue& Value)
{
	if(!IsPossesedByCutscene)
	{
		Owner->AddControllerYawInput(Value.Get<float>());	
	}
}
