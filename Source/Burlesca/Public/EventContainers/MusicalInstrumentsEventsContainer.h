// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MusicalInstrumentsEventsContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGuitarActivate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnXylophoneActivate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddMoney, int64, quantity);

UCLASS()
class BURLESCA_API UMusicalInstrumentsEventsContainer : public UObject
{
	GENERATED_BODY()

public:
	FOnGuitarActivate OnGuitarActivate;
	FOnXylophoneActivate OnXylophoneActivate;
	FOnAddMoney OnAddMoney;

	void TryBroadcastEventByName(FName name)
	{
		if(name == FName("GuitarActivate"))
			OnGuitarActivate.Broadcast();
		else if(name == FName("XylophoneActivate"))
			OnXylophoneActivate.Broadcast();
	}

	template<typename T>
	void TryBroadcastEventByName_OneParam(FName name, T firstParam)
	{
		/*switch(name)
		{
		case FName("AddMoney"):
				bool isSame = typeid(T) == typeid(OnAddMoney);
				OnAddMoney.Broadcast(firstParam);
				break;
		}*/		
	}

	template<typename T, typename U>
	void TryBroadcastEventByName_TwoParam(FName name, T firstParam, U secondParam)
	{
		
	}
	
	template<typename T, typename U, typename V>
	void TryBroadcastEventByName_ThreeParam(FName name, T firstParam, U secondParam, V thirdParam)
	{
			
	}
};
