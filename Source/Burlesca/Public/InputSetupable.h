// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputSetupable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInputSetupable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BURLESCA_API IInputSetupable
{
	GENERATED_BODY()

public:
	virtual void SetupInput(UEnhancedInputComponent* InputComponent) = 0;
};
