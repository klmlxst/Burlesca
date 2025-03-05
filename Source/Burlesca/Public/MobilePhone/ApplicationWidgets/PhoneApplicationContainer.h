// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MobilePhone/MobilePhone.h"
#include "PhoneApplicationContainer.generated.h"

class UGuitarTunerScreen;
class UFlashlightScreen;
class UChatScreen;
class UHomeScreen;
/**
 * 
 */
UCLASS()
class BURLESCA_API UPhoneApplicationContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetContainerVisibility(ESlateVisibility visibility);
	
	UPhoneApplication* GetCurrentOpenedApplication();
	UPhoneApplication* GetApplicationWidget(EPhoneApplication app);
	void ActivateCurrentApplication();
	void DeactivateCurrentApplication();
	
protected:
	UFUNCTION()
	void OpenApplication(EPhoneApplication application);

	UFUNCTION()
	void OnApplicationClosed();
	
	/*  ---  Application Widgets  ---  */
	
	UPROPERTY(meta=(BindWidget))
	UHomeScreen* HomeScreenWidget;

	UPROPERTY(meta=(BindWidget))
	UChatScreen* ChatScreenWidget;

	UPROPERTY(meta=(BindWidget))
	UFlashlightScreen* FlashlightWidget;

	UPROPERTY(meta=(BindWidget))
	UGuitarTunerScreen* GuitarTunerScreenWidget;
	
	EPhoneApplication OpenedPhoneApplication = EPhoneApplication::HomePage;

	UPROPERTY()
	TMap<EPhoneApplication, UPhoneApplication*> ApplicationEnumToWidgetMap;
};
