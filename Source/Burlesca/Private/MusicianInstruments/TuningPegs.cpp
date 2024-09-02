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
	if(!bIsRotating && !bIsTuned)
	{
		bIsRotating = true;
		GetWorldTimerManager().SetTimer(RotationReload, this, &ATuningPegs::SetIsNotRotating, 0.01f);
		
		switch(RotationDirection)
		{
			case ERotationDirection::Left:
				if(CurrentRotation - 0.02f > MinRotation)
					CurrentRotation -= 0.02f;
			break;
			
			case ERotationDirection::Right:
				if(CurrentRotation + 0.02f < MaxRotation)
					CurrentRotation += 0.02f;
			break;
		}

		UpdateRelativeRotationViaCurrentRotationValue();

		if(CurrentRotation >= 4.98f && CurrentRotation <= 5.02f)
		{
			bIsTuned = true;
			SetComplete();
		}
	}
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

void ATuningPegs::BeginPlay()
{
	Super::BeginPlay();

	InitializeRotationRange();
}

void ATuningPegs::UpdateRelativeRotationViaCurrentRotationValue()
{
	SetActorRelativeRotation(FRotator(CurrentRotation * 30, 0.0f, 0.0f));
}
