// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SettingsContainer.generated.h"

class UInputSettingsContainer;
/**
 * 
 */
UCLASS()
class BURLESCA_API USettingsContainer : public UObject
{
	GENERATED_BODY()

public:
	USettingsContainer();

	UInputSettingsContainer* GetInputSettingsContainer() const { return InputSettingsContainer; }

protected:
	UPROPERTY()
	UInputSettingsContainer* InputSettingsContainer;
};
