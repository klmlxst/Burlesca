// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Replic.generated.h"

/**
 * @class UReplic
 * @brief  This class storage replic
 * Class provides metod in setting text and time view, and
 * also to receive current replic.
 * It using on storage data the replic/
 * 
 */
UCLASS()
class BURLESCA_API UReplic : public UObject
{
	GENERATED_BODY()
public:

	float GetDisplayReplic() const;
	/*
	 * Return current replic
	 * @return FText current replic
	 */
	FText GetReplic() const;

	/*
	 * Setting text replic and time on vision
	 * @param Replic text new replic
	 * @param DelataReplic Time, during witch do view
	 */
	void SetReplic(FText Replic, float DelataReplic);
	
protected:
	UPROPERTY(EditAnywhere, Category = "Replic Data")
	FText ReplicText;

	UPROPERTY(EditAnywhere, Category = "Replic Data")
	float DisplayTime;
};
