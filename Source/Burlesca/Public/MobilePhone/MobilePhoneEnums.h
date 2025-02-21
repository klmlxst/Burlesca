// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MobilePhoneEnums.generated.h"

/**
 * 
 */

UENUM()
enum class EPhoneApplication : uint8
{
	None = 0,
	HomePage = 1,
	GuitarSetup = 2,
	Chat = 3,
	Flashlight = 4
};

UENUM()
enum class EPhoneSituation : uint8
{
	InPocket,
	InHands,
	InWorld
};
