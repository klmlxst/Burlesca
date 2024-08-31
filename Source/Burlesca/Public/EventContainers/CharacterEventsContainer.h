// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterEventsContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterCameraMovedOutFromCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterCameraMovedToCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterCameraEndMovement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSetupInputComponent, UInputComponent*, InputComponent);

/**
 * 
 */
UCLASS()
class BURLESCA_API UCharacterEventsContainer : public UObject
{
	GENERATED_BODY()

public:
	FOnCharacterCameraMovedOutFromCharacter OnCharacterCameraMovedOutFromCharacter;
	FOnCharacterCameraMovedToCharacter OnCharacterCameraReturnedToCharacter;
	FOnCharacterCameraEndMovement OnCharacterCameraEndMovement;
	FOnCharacterSetupInputComponent OnCharacterSetupInputComponent;
};
