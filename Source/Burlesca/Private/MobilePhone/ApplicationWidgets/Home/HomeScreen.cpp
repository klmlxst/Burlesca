﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/ApplicationWidgets/Home/HomeScreen.h"

#include "EnhancedInputComponent.h"
#include "MobilePhone/MobilePhoneEnums.h"
#include "MobilePhone/ApplicationWidgets/Home/ApplicationIcon.h"

void UHomeScreen::SetupInput(UEnhancedInputComponent* input)
{
	input->BindAction(HorizontalChooseAnotherApplicationAction, ETriggerEvent::Started, this, &UHomeScreen::OnHorizontalChooseAnotherApplicationActionCalled);
	input->BindAction(VerticalChooseAnotherApplicationAction, ETriggerEvent::Started, this, &UHomeScreen::OnVerticalChooseAnotherApplicationActionCalled);
	input->BindAction(OpenApplicationAction, ETriggerEvent::Started, this, &UHomeScreen::OnOpenApplicationActionCalled);
}

void UHomeScreen::NativeConstruct()
{
	ApplicationIcons.Add(FlashlightApplicationIcon);
	ApplicationIcons.Add(ChatApplicationIcon);
	ApplicationIcons.Add(GuitarSalmonApplicationIcon);
}

void UHomeScreen::OpenApplication()
{
	Super::OpenApplication();
	
	CurrentSelectedApplicationIcon = 0;
	ApplicationIcons[CurrentSelectedApplicationIcon]->Select();
}

void UHomeScreen::CloseApplication()
{
	Super::CloseApplication();
	
	ApplicationIcons[CurrentSelectedApplicationIcon]->Deselect();
	CurrentSelectedApplicationIcon = 0;
}

void UHomeScreen::OnHorizontalChooseAnotherApplicationActionCalled(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("b"));

	if(bIsApplicationActive)
	{
		UE_LOG(LogTemp,Warning,TEXT("OnHorizontalChooseAnotherApplicationActionCalled"));
		
		ApplicationIcons[CurrentSelectedApplicationIcon]->Deselect();
		if(Value.Get<float>() > 0 && CurrentSelectedApplicationIcon < ApplicationIcons.Num()-1)
		{
			UE_LOG(LogTemp,Warning,TEXT("a"));

			CurrentSelectedApplicationIcon++;
		}
		else if(Value.Get<float>() < 0 && CurrentSelectedApplicationIcon != 0)
		{
			CurrentSelectedApplicationIcon--;
		}
		ApplicationIcons[CurrentSelectedApplicationIcon]->Select();
	}
}

void UHomeScreen::OnVerticalChooseAnotherApplicationActionCalled(const FInputActionValue& Value)
{
	if(bIsApplicationActive)
	{
		ApplicationIcons[CurrentSelectedApplicationIcon]->Deselect();
		if(Value.Get<float>() > 0 && CurrentSelectedApplicationIcon + 3 <= ApplicationIcons.Num()-1)
		{
			CurrentSelectedApplicationIcon += 3;
		}
		else if(Value.Get<float>() < 0 && CurrentSelectedApplicationIcon-3 >= 0)
		{
			CurrentSelectedApplicationIcon -= 3;
		}
		ApplicationIcons[CurrentSelectedApplicationIcon]->Select();
	}
}

void UHomeScreen::OnOpenApplicationActionCalled()
{
	if(bIsApplicationActive)
	{
		switch(CurrentSelectedApplicationIcon)
		{
		case 0:
			OnApplicationOpenCalled.Broadcast(EPhoneApplication::Flashlight);
			break;
		
		case 1:
			OnApplicationOpenCalled.Broadcast(EPhoneApplication::Chat);
			break;
		
		case 2:
			OnApplicationOpenCalled.Broadcast(EPhoneApplication::GuitarSetup);
			break;
		}
	}
}