// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MobilePhone/ApplicationWidgets/PhoneApplication.h"
#include "ChatScreen.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UChatScreen : public UPhoneApplication
{
	GENERATED_BODY()

public:
	virtual void SetupInput(UEnhancedInputComponent* input) override;
};
