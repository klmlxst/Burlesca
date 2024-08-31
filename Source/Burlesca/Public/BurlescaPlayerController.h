// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BurlescaPlayerController.generated.h"

class AGameplayHUD;
class USignalBus;
/**
 * 
 */
UCLASS()
class BURLESCA_API ABurlescaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void Init(USignalBus* signalBus);
	void PauseGame();
	void UnpauseGame();
	
	FORCEINLINE bool GetIsGamePaused() const { return bIsGamePaused; }

protected:
	bool bIsGamePaused;

	UPROPERTY()
	USignalBus* SignalBus;
};
