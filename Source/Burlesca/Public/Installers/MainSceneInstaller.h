// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputSetupable.h"
#include "Framework/DependencyInjection/InjectionInstaller.h"
#include "MainSceneInstaller.generated.h"

class UMobilePhoneController;
class USettingsContainer;
class UInputMappingContext;
class ABurlescaPlayerController;
class AMainCharacter;
class UInputAction;
class UEscapeButtonController;
class USignalBus;
class AMobilePhone;
/**
 * 
 */
UCLASS()
class BURLESCA_API AMainSceneInstaller : public AInjectionInstaller, public IInputSetupable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	USignalBus* SignalBus;

	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	USettingsContainer* SettingsContainer;

	/*  ---  Player Controller  ---  */
	
	UPROPERTY(VisibleAnywhere)
	ABurlescaPlayerController* PlayerController;
	
	UPROPERTY(EditInstanceOnly, Category = "PlayerController")
	TSubclassOf<APlayerController> PlayerControllerClass;

	UPROPERTY(EditInstanceOnly, Category = "PlayerController")
	UInputMappingContext* MappingContext;

	/*  ---  Escape Button Controller  ---  */
	
	UPROPERTY()
	UEscapeButtonController* EscapeButtonController;
	
	UPROPERTY(EditInstanceOnly, Category = "EscapeController")
	UInputAction* EscapeButtonPressedAction;

	/*  ---  Mobile Phone Controller  ---  */

	UPROPERTY()
	UMobilePhoneController* MobilePhoneController;

	UPROPERTY()
	AMobilePhone* MobilePhone;	

	UPROPERTY(EditInstanceOnly, Category = "MobilePhoneController")
	UInputAction* TakePhoneInOrOutOfHandsAction;

	/*  ---  Functions  ---  */
	
	virtual void InstallBindings(UDependencyContainer* Container) override;
	virtual void Start(UDependencyContainer* Container) override;
	virtual void SetupInput(UEnhancedInputComponent* InputComponent) override;
};
