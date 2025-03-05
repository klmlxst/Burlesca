// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/ApplicationWidgets/PhoneApplication.h"

void UPhoneApplication::SetupInput(UEnhancedInputComponent* input)
{
}

void UPhoneApplication::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPhoneApplication::OpenApplication()
{	
	SetVisibility(ESlateVisibility::Visible);
	bIsApplicationOpened = true;
}

void UPhoneApplication::CloseApplication()
{
	OnApplicationClosed.Broadcast();
	DeactivateApplication();
	SetVisibility(ESlateVisibility::Collapsed);
	bIsApplicationOpened = false;
}

void UPhoneApplication::ActivateApplication()
{
	bIsApplicationActive = true;
}

void UPhoneApplication::DeactivateApplication()
{
	bIsApplicationActive = false;
}
