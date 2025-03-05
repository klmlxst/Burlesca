// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputSetupable.h"
#include "MobilePhoneEnums.h"
#include "ApplicationWidgets/PhoneApplication.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "MobilePhone.generated.h"

class UPhoneApplicationContainer;
enum class EPhoneApplication : uint8;
class UWidgetComponent;

UCLASS()
class BURLESCA_API AMobilePhone : public AActor
{
	GENERATED_BODY()

public:
	AMobilePhone();
	void Init();
	
	UFUNCTION()
	void SetPowerState(bool bPowerOn) const;

	UFUNCTION()
	void SetVisibility(bool bIsVisible) const;
	
	void OnPhoneFocused();
	void OnPhoneUnfocused();
	UPhoneApplication* GetApp(EPhoneApplication app);
	
	void PlayNotificationSound() const { AudioComponent->Play();  }
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPhoneApplicationContainer> ApplicationsContainerClass;
	
	UPROPERTY()
	UPhoneApplicationContainer* ApplicationsContainer;
	
	UPROPERTY(EditAnywhere)
	UWidgetComponent* MobilePhoneScreenWidgetComponent;

	/*  ---  Notification  ---  */
	
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* NotificationSound;
};
