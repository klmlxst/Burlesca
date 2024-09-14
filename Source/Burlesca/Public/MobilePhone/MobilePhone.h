// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/DependencyInjection/Inject.h"
#include "GameFramework/Actor.h"
#include "MobilePhone.generated.h"

class UMobilePhoneController;
class UWidgetComponent;
class UMobilePhoneScreen;

UCLASS()
class BURLESCA_API AMobilePhone : public AActor
{
	GENERATED_BODY()

public:
	AMobilePhone();

	UFUNCTION()
	void SetPowerState(bool bPowerOn);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* MobilePhoneScreenWidgetComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMobilePhoneScreen> MobilePhoneScreenClass;

	UPROPERTY(VisibleDefaultsOnly)
	UMobilePhoneScreen* MobilePhoneScreenWidget;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;
	
};
