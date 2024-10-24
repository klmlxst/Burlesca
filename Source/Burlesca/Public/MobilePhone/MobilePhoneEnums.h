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
	None,
	HomePage,
	GuitarSetup,
	Chat,
	Flashlight
};

UENUM()
enum class EPhoneSituation : uint8
{
	InPocket,
	InHands,
	InWorld
};
