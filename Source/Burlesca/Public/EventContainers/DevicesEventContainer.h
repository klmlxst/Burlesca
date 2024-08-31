// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DevicesEventContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhoneFocused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhoneUnfocused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhoneTakedInHands);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhonePutInInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhonePlacedInWorld);

/**
 * 
 */
UCLASS()
class BURLESCA_API UDevicesEventContainer : public UObject
{
	GENERATED_BODY()

public:
	FOnPhoneFocused OnPhoneFocused;
	FOnPhoneUnfocused OnPhoneUnfocused;
	FOnPhoneTakedInHands OnPhoneTakedInHands;
	FOnPhonePutInInventory OnPhonePutInInventory;
	FOnPhonePlacedInWorld OnPhonePlacedInWorld;
};
