// Copyright Uncertain Studios (c). All Rights Reserved.


#include "InteractableObjects/DefaultInteractableObject.h"

ADefaultInteractableObject::ADefaultInteractableObject()
{
}

void ADefaultInteractableObject::StartFocus()
{
	UE_LOG(LogTemp,Warning,TEXT("Called focus"));

}

void ADefaultInteractableObject::StartSemiFocus()
{
	UE_LOG(LogTemp,Warning,TEXT("Called semi-focus"));
}

void ADefaultInteractableObject::EndFocus()
{
	UE_LOG(LogTemp,Warning,TEXT("Called unfocus"));
}

void ADefaultInteractableObject::Interact()
{
	UE_LOG(LogTemp,Warning,TEXT("Called interaction"));

}

FInteractableObjectInfo* ADefaultInteractableObject::GetInteractableObjectInfo() { return &InteractableObjectInfo; }

void ADefaultInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}
