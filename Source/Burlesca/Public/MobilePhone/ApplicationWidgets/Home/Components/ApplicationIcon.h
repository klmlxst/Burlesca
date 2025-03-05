// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ApplicationIcon.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class BURLESCA_API UApplicationIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	void Select();
	void Deselect();

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UImage* Icon;
	
	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UImage* SelectBorder;
};
