// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventContainers/CharacterEventsContainer.h"
#include "EventContainers/DevicesEventContainer.h"
#include "EventContainers/GlobalGameEventsContainer.h"
#include "SignalBus.generated.h"

class UDevicesEventContainer;
class UGlobalGameEventsContainer;
class UCharacterEventsContainer;
/**
 * 
 */
UCLASS()
class BURLESCA_API USignalBus : public UObject
{
	GENERATED_BODY()

public:
	USignalBus()
	{
		CharacterEventsContainer = CreateDefaultSubobject<UCharacterEventsContainer>(TEXT("Characters Event Container"));
		GlobalGameEventsContainer = CreateDefaultSubobject<UGlobalGameEventsContainer>(TEXT("Global Game Event Container"));
		DevicesEventContainer = CreateDefaultSubobject<UDevicesEventContainer>(TEXT("Device Event Container"));
	}

	UFUNCTION()
	UCharacterEventsContainer* GetCharacterEventsContainer() const
	{ return CharacterEventsContainer; }

	UFUNCTION()
	UGlobalGameEventsContainer* GetGlobalGameEventsContainer() const
	{ return GlobalGameEventsContainer; }

	UFUNCTION()
	UDevicesEventContainer* GetDevicesEventContainer() const
	{ return DevicesEventContainer; }
	
protected:

	UPROPERTY()
	UCharacterEventsContainer* CharacterEventsContainer;

	UPROPERTY()
	UGlobalGameEventsContainer* GlobalGameEventsContainer;

	UPROPERTY()
	UDevicesEventContainer* DevicesEventContainer;
};
