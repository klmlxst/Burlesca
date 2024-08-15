// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects/DefaultInteractableObject.h"
#include "TakeToHandsInteractableObject.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API ATakeToHandsInteractableObject : public ADefaultInteractableObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
