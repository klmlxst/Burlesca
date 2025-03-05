// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PhoneApplication.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnApplicationClosed);

UCLASS()
class BURLESCA_API UPhoneApplication : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetupInput(UEnhancedInputComponent* input);
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	virtual void OpenApplication();
	
	UFUNCTION(BlueprintCallable)
	virtual void CloseApplication();

	virtual void ActivateApplication();
	virtual void DeactivateApplication();
	
	bool GetIsApplicationOpened() { return bIsApplicationOpened; }
	bool GetIsApplicationActive() { return bIsApplicationOpened; }

	FOnApplicationClosed OnApplicationClosed;

protected:
	bool bIsApplicationOpened = false;
	bool bIsApplicationActive = false;
};
