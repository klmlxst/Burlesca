// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReplicStorage.generated.h"

class UReplic;
/**
 * @class UReplicStorage storage array UReplic
 * This class storage array UReplic.
 */
UCLASS()
class BURLESCA_API UReplicStorage : public UDataAsset
{
	GENERATED_BODY()
public:
	/*
	 * Append UReplic in array
	 * @param UReplic class storage replic.
	 */
	void AppednReplic(UReplic* Replic);
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<UReplic*> Dialog; 
};
