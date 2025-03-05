// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/SettingsContainer.h"

#include "Settings/InputSettingsContainer.h"

USettingsContainer::USettingsContainer()
{
	InputSettingsContainer = CreateDefaultSubobject<UInputSettingsContainer>(TEXT("InputSettingsContainer"));
	InputSettingsContainer->SetMouseSensitivity(1);
}
