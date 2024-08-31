// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_MainCharacterCameraController.generated.h"

class USignalBus;
class AGameplayHUD;
class UCameraComponent;
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
class UInputSettingsContainer;

struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BURLESCA_API UTP_MainCharacterCameraController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTP_MainCharacterCameraController();
	void Init(UCameraComponent* camera, USignalBus* signalBus, UInputSettingsContainer* InputSettingsContainer);
	void SetupInput(UEnhancedInputComponent* input);
	void PlayService();
	void StopService();

	FORCEINLINE bool IsServiceStoped() const { return bIsServiceStoped; }

	void MoveCameraTo(AActor* PositionActor, float MovementDuration, bool bIsMovingFromCharacter, bool bIsMovingToCharacter = false);
	void MoveCameraTo(FVector PositionVector, FRotator RotationVector, float MovementDuration, bool bIsMovingFromCharacter, bool bIsMovingToCharacter = false);
	void ReturnCameraToCharacter(float MovementDuration);

protected:
	UPROPERTY()
	UCameraComponent* MainCamera;

	UPROPERTY()
	ACharacter* Owner;
	
	UPROPERTY()
	USignalBus* SignalBus;

	UPROPERTY()
	UInputSettingsContainer* InputSettingsContainer;
	
	bool bIsServiceStoped;

	/* ---  Camera Input Setup  --- */
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookXAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookYAction;

	void LookUp(const FInputActionValue& Value);
	void LookRight(const FInputActionValue& Value);
	
	/* ---  Camera Movement To Position  --- */
	
	void UpdateCameraPosition();
	
	FVector OnPlayerCameraPosition;
	FRotator OnPlayerCameraRotator;

	FVector StartCameraPosition;
	FRotator StartCameraRotation;
	
	FVector TargetCameraPosition;
	FRotator TargetCameraRotation;
	
	float LerpSpeed;
	float TimeElapsed;

	FTimerHandle CameraMovementTimerHandle;

	bool bIsCameraOnCharacter = true;
	bool bIsCameraMovingToCharacter;
};
