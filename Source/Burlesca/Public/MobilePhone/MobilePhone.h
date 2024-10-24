// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputSetupable.h"
#include "GameFramework/Actor.h"
#include "MobilePhone.generated.h"

class UGuitarTunerScreen;
class UFlashlightScreen;
class UChatScreen;
enum class EPhoneApplication : uint8;
class UHomeScreen;
class UMobilePhoneController;
class UWidgetComponent;

UCLASS()
class BURLESCA_API AMobilePhone : public AActor, public IInputSetupable
{
	GENERATED_BODY()

public:
	AMobilePhone();
	virtual void SetupInput(UEnhancedInputComponent* Input) override;
	
	UFUNCTION()
	void SetPowerState(bool bPowerOn);
	void SetVisibility(bool bIsVisible) const;
	void OnPhoneFocused();
	void OnPhoneUnfocused();
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	EPhoneApplication OpenedPhoneApplication;
protected:
	void WidgetsCreation();

	UFUNCTION()
	void OpenApplication(EPhoneApplication application);
	
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* MobilePhoneScreenWidgetComponent;
	
	/*  ---  Application Widget Classes  ---  */
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHomeScreen> HomeScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UChatScreen> ChatScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFlashlightScreen> FlashlightWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGuitarTunerScreen> GuitarTunerWidgetClass;

	/*  ---  Application Widgets  ---  */
	
	UPROPERTY(VisibleDefaultsOnly)
	UHomeScreen* HomeScreenWidget;

	UPROPERTY(VisibleDefaultsOnly)
	UChatScreen* ChatScreenWidget;

	UPROPERTY(VisibleDefaultsOnly)
	UFlashlightScreen* FlashlightWidget;

	UPROPERTY(VisibleDefaultsOnly)
	UGuitarTunerScreen* GuitarTunerScreenWidget;
};
