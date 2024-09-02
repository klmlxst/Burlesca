// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicianInstruments/TuningPegs.h"


// Sets default values
ATuningPegs::ATuningPegs()
{
   StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);
}

void ATuningPegs::Select()
{
	StaticMeshComponent->SetRenderCustomDepth(true);
	StaticMeshComponent->SetCustomDepthStencilValue(2);
}

void ATuningPegs::Deselect()
{
	StaticMeshComponent->SetCustomDepthStencilValue(0);
	StaticMeshComponent->SetRenderCustomDepth(false);
}

void ATuningPegs::Rotate(ERotationDirection RotationDirection)
{
	if(!bIsRotating)
	{
		switch(RotationDirection)
		{
		case ERotationDirection::Left:
			bIsRotating = true;
			GetWorldTimerManager().SetTimer(RotationReload, this, &ATuningPegs::SetIsNotRotating, 0.01f);
			CurrentRotation -= 0.02f;
			UpdateRelativeRotationViaCurrentRotationValue();
			break;
			
		case ERotationDirection::Right:
			bIsRotating = true;
			GetWorldTimerManager().SetTimer(RotationReload, this, &ATuningPegs::SetIsNotRotating, 0.01f);
			CurrentRotation += 0.02f;
			UpdateRelativeRotationViaCurrentRotationValue();
			break;
		}
	}
	
	

	/*switch (RotationDirection) {
	case ERotationDirection::Left:
		NewRotation -= RotationSpeed;
		break;
	case ERotationDirection::Right:
		NewRotation += RotationSpeed;
		break;
	}
	
	if (NewRotation >= MinRotation && NewRotation <= MaxRotation) {
		CurrentRotation = NewRotation;
		SetActorRelativeRotation(FRotator(0.0f, 0.0f, CurrentRotation));
	}*/
}

void ATuningPegs::SetComplete()
{
	StaticMeshComponent->SetRenderCustomDepth(true);
	StaticMeshComponent->SetCustomDepthStencilValue(1);
}

float ATuningPegs::GetCurrentRotation() const
{
	return CurrentRotation;
}

void ATuningPegs::InitializeRotationRange()
{
	if (FMath::RandBool()) {
		CurrentRotation = FMath::RandRange(1.5f, 3.5f);
	} else {
		CurrentRotation = FMath::RandRange(6.5f, 8.5f);
	}

	UpdateRelativeRotationViaCurrentRotationValue();
}

bool ATuningPegs::IsTuned() const
{
	return bIsTuned;
}

void ATuningPegs::BeginPlay()
{
	Super::BeginPlay();

	InitializeRotationRange();
}

void ATuningPegs::UpdateRelativeRotationViaCurrentRotationValue()
{
	SetActorRelativeRotation(FRotator(CurrentRotation * 30, 0.0f, 0.0f));
}
