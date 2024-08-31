// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/GuitarInteractableObject.h"

#include "MainCharacter.h"
#include "MusicianInstruments/GuitarSetupController.h"


AGuitarInteractableObject::AGuitarInteractableObject()
{
	
}

void AGuitarInteractableObject::Inject(UDependencyContainer* Container)
{
	Super::Inject(Container);

	GuitarSetupController = Container->Resolve<UGuitarSetupController>();
	check(GuitarSetupController);
}


void AGuitarInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

void AGuitarInteractableObject::Interact()
{
	Super::Interact();

	GuitarSetupController->StartGuitarSetup();
	
}

