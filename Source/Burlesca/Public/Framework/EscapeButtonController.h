// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EscapeButtonController.generated.h"

class ABurlescaPlayerController;
class UGuitarSetupController;
class USignalBus;
class UEnhancedInputComponent;
class UInputAction;
class AMainCharacter;
/**
 * 
 */
UCLASS()
class BURLESCA_API UEscapeButtonController : public UObject
{
	GENERATED_BODY()

public:
	void Init(USignalBus* signalBus, UInputAction* escapeButton, AMainCharacter* mainCharacter,
		ABurlescaPlayerController* playerController);
	void InitServicies(UGuitarSetupController* guitarSetupController);
	
	UFUNCTION()
	void SetupInput(UEnhancedInputComponent* InputComponent);
protected:
	UFUNCTION()
	void ProcessEscapeData();
	
	UPROPERTY()
	UInputAction* EscapeButtonPressed;

	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	ABurlescaPlayerController* PlayerController;

	UPROPERTY()
	USignalBus* SignalBus;

	/* ---  Service Dependencies  --- */

	UPROPERTY()
	UGuitarSetupController* GuitarSetupController;

	bool bIsGamePaused;
	bool bIsCameraReturningToPlayer;

	UFUNCTION()
	void SetIsCameraReturningToPlayerToFalse();
};
