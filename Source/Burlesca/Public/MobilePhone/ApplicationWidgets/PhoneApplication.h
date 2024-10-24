// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PhoneApplication.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UPhoneApplication : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetupInput(UEnhancedInputComponent* input);
	virtual void NativeConstruct() override;
	
	virtual void OpenApplication();
	virtual void CloseApplication();
	virtual void ActivateApplication();
	virtual void DeactivateApplication();

	bool GetIsApplicationOpened() { return bIsApplicationOpened; }
	bool GetIsApplicationActive() { return bIsApplicationOpened; }

protected:
	bool bIsApplicationOpened = false;
	bool bIsApplicationActive = false;
};
