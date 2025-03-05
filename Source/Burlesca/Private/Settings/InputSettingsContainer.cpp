// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/InputSettingsContainer.h"

void UInputSettingsContainer::SetMouseSensitivity(float Value)
{
	if(Value > 0)
	{
		MouseSensitivity = Value;
	}
}
