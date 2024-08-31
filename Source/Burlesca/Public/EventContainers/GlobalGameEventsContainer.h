// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GlobalGameEventsContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUnpaused);

/**
 * 
 */
UCLASS()
class BURLESCA_API UGlobalGameEventsContainer : public UObject
{
	GENERATED_BODY()
public:
	FOnGamePaused OnGamePaused;
	FOnGameUnpaused OnGameUnpaused;
};
