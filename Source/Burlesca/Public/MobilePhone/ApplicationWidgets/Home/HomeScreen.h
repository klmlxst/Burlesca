// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HomeScreen.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnApplicationOpenCalled, EPhoneApplication, ChosenApplication);

class UEnhancedInputComponent;
class UApplicationIcon;
class UInputAction;

struct FInputActionValue;


/**
 * 
 */
UCLASS()
class BURLESCA_API UHomeScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnApplicationOpenCalled OnApplicationOpenCalled;

	void SetupInput(UEnhancedInputComponent* input);
	void NativeConstruct() override;
	
	void OpenApplication();
	void CloseApplication();
	void ActivateApplication();
	void DeactivateApplication();
	
protected:
	UPROPERTY(EditAnywhere)
	UInputAction* HorizontalChooseAnotherApplicationAction;

	UPROPERTY(EditAnywhere)
	UInputAction* VerticalChooseAnotherApplicationAction;

	UPROPERTY(EditAnywhere)
	UInputAction* OpenApplicationAction;

	void OnHorizontalChooseAnotherApplicationActionCalled(const FInputActionValue& Value);
	void OnVerticalChooseAnotherApplicationActionCalled(const FInputActionValue& Value);
	void OnOpenApplicationActionCalled();
	
	UPROPERTY(meta=(BindWidget))
	UApplicationIcon* HomeApplicationIcon;

	UPROPERTY(meta=(BindWidget))
	UApplicationIcon* ChatApplicationIcon;

	UPROPERTY()
	TArray<UApplicationIcon*> ApplicationIcons;
	
	uint8 CurrentSelectedApplicationIcon = 0;
	bool bIsApplicationOpened = false;
	bool bIsApplicationActive = false;
};
