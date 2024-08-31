// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/ComputerInteractableObject.h"

#include "MainCharacter.h"
#include "Components/WidgetComponent.h"
#include "HUD/ComputerScreen.h"

AComputerInteractableObject::AComputerInteractableObject()
{
	ComputerScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Computer Screen Widget"));
	ComputerScreenWidgetComponent->SetupAttachment(RootComponent);
	ComputerScreenWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
}

void AComputerInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	if(ComputerScreenWidgetComponent && ComputerScreenClass)
	{
		ComputerScreenWidget = CreateWidget<UComputerScreen>(GetWorld(), ComputerScreenClass);

		if(ComputerScreenWidget)
		{
			ComputerScreenWidgetComponent->SetWidget(ComputerScreenWidget);
		}
	}
}

void AComputerInteractableObject::Interact()
{
	Super::Interact();

	MainCharacter->MoveCameraTo(Actor, 2.0f, true);
}
