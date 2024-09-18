// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/ApplicationWidgets/Home/HomeScreen.h"

#include "EnhancedInputComponent.h"
#include "MobilePhone/ApplicationWidgets/Home/ApplicationIcon.h"

void UHomeScreen::SetupInput(UEnhancedInputComponent* input)
{
	input->BindAction(HorizontalChooseAnotherApplicationAction, ETriggerEvent::Started, this, &UHomeScreen::OnHorizontalChooseAnotherApplicationActionCalled);
	input->BindAction(VerticalChooseAnotherApplicationAction, ETriggerEvent::Started, this, &UHomeScreen::OnVerticalChooseAnotherApplicationActionCalled);
	input->BindAction(OpenApplicationAction, ETriggerEvent::Started, this, &UHomeScreen::OnOpenApplicationActionCalled);
}

void UHomeScreen::NativeConstruct()
{
	ApplicationIcons.Add(HomeApplicationIcon);
	ApplicationIcons.Add(ChatApplicationIcon);
}

void UHomeScreen::OpenApplication()
{
	SetVisibility(ESlateVisibility::Visible);
	CurrentSelectedApplicationIcon = 0;
	ApplicationIcons[CurrentSelectedApplicationIcon]->Select();
}

void UHomeScreen::CloseApplication()
{
	SetVisibility(ESlateVisibility::Collapsed);
	ApplicationIcons[CurrentSelectedApplicationIcon]->Deselect();
	CurrentSelectedApplicationIcon = 0;
}

void UHomeScreen::ActivateApplication()
{
	bIsApplicationActive = true;
}

void UHomeScreen::DeactivateApplication()
{
	bIsApplicationActive = false;
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
}
