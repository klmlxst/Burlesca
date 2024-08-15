// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CircularProgressBar.generated.h"


class UImage;

UCLASS()
class BURLESCA_API UCircularProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Progress Bar")
	void SetPercentage(float percentage);
	
};

