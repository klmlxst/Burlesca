// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ConditionTooltip.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UConditionTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetText(FText text) const
	{
		Text->SetText(text);
		UE_LOG(LogTemp, Log, TEXT("Set text : %s"), *text.ToString()) 
	}
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text;
};
