// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MobilePhone/ApplicationWidgets/PhoneApplication.h"
#include "FlashlightScreen.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UFlashlightScreen : public UPhoneApplication
{
	GENERATED_BODY()

public:
	void SetupInput(UEnhancedInputComponent* input) override;
};
