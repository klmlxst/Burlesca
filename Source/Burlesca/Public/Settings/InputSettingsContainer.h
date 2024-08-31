// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputSettingsContainer.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UInputSettingsContainer : public UObject
{
	GENERATED_BODY()

public:
	float GetMouseSensitivity() const { return MouseSensitivity; }
	void SetMouseSensitivity(float Value);

	bool bIsMouseInvertedY;
	bool bIsMouseInvertedX;
protected:
	float MouseSensitivity;
	
};
