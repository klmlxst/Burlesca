// Copyright Uncertain Studios (c). All Rights Reserved.


#include "InteractableObjects/DefaultInteractableObject.h"

#include "MainCharacter.h"
#include "Framework/SignalBus.h"
#include "Framework/DependencyInjection/DependencyInjection.h"


ADefaultInteractableObject::ADefaultInteractableObject()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMeshComponent);
}

void ADefaultInteractableObject::StartFocus()
{
	if(InteractableObjectInfo.ActivityState == EInteractableObjectActivityState::Active &&
		InteractableObjectInfo.InteractionType != EInteractableObjectType::Hidden &&
		InteractableObjectInfo.InteractionType != EInteractableObjectType::Putdown)
	{
		StaticMeshComponent->SetRenderCustomDepth(true);
		StaticMeshComponent->SetCustomDepthStencilValue(4);
	}

	if(InteractableObjectInfo.ActivityState == EInteractableObjectActivityState::Active &&
		InteractableObjectInfo.InteractionType == EInteractableObjectType::Putdown)
	{
		StaticMeshComponent->SetRenderCustomDepth(true);
		StaticMeshComponent->SetCustomDepthStencilValue(5);
	}
}

void ADefaultInteractableObject::StartSemiFocus()
{
	if(InteractableObjectInfo.InteractionType != EInteractableObjectType::Hidden)
	{
		StaticMeshComponent->SetRenderCustomDepth(true);
		StaticMeshComponent->SetCustomDepthStencilValue(5);	
	}
}

void ADefaultInteractableObject::EndFocus()
{
	StaticMeshComponent->SetCustomDepthStencilValue(5);
	StaticMeshComponent->SetRenderCustomDepth(false);
}

void ADefaultInteractableObject::Interact()
{
	
}

FInteractableObjectInfo* ADefaultInteractableObject::GetInteractableObjectInfo() { return &InteractableObjectInfo; }

void ADefaultInteractableObject::Inject(UDependencyContainer* Container)
{
	MainCharacter = Container->Resolve<AMainCharacter>();
	SignalBus = Container->Resolve<USignalBus>();

	check(MainCharacter);
	check(SignalBus);
}
