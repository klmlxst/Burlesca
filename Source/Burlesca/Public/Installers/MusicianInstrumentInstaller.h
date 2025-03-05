// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <InputSetupable.h>

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Framework/DependencyInjection/InjectionInstaller.h"
#include "MusicianInstrumentInstaller.generated.h"

class UInputAction;
class ATuningPegs;
class UGuitarSetupController;
class APointLight;
class UInstrumentController;

UCLASS()
class BURLESCA_API AMusicianInstrumentInstaller : public AInjectionInstaller, public IInputSetupable
{
	GENERATED_BODY()

public:
	virtual void InstallBindings(UDependencyContainer* Container) override;
	virtual void SetupInput(UEnhancedInputComponent* EnhancedInputComponent) override;

protected:
	UPROPERTY()
	UGuitarSetupController* GuitarSetupController;
	
	/*  ---  Guitar  ---  */
	UPROPERTY(EditAnywhere, Category="Setup|Guitar Input")
	UInputAction* SwitchPegAction;

	UPROPERTY(EditAnywhere, Category="Setup|Guitar Input")
	UInputAction* RotatePegAction;

	UPROPERTY(EditAnywhere, Category="Setup|Guitar Input")
	UInputAction* PlayStringAction;
	
	UPROPERTY(EditAnywhere, Category="Setup|Guitar Setup")
	TArray<ATuningPegs*> TuningPegs;
	
	UPROPERTY(EditAnywhere, Category = "Setup|Guitar Setup")
	AActor* GuitarSetupViewPlaceholder;
	
	UPROPERTY(EditAnywhere, Category = "Setup|Guitar Setup")
	APointLight* LeftLight;
	
	UPROPERTY(EditAnywhere, Category = "Setup|Guitar Setup")
	APointLight* RightLight;

	UPROPERTY(EditAnywhere, Category = "Setup|Guitar Setup|Audio")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Setup|Guitar Setup|Audio")
	USoundBase* SuccessSound;
	
	UPROPERTY(EditAnywhere, Category = "Setup|Guitar Setup|Audio")
	TArray<USoundBase*> StringSounds;
	
};