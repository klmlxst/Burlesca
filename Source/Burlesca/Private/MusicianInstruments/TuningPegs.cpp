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
	float NewRotation = CurrentRotation;

	switch (RotationDirection) {
	case ERotationDirection::Left:
		NewRotation -= RotationSpeed;
		break;
	case ERotationDirection::Right:
		NewRotation += RotationSpeed;
		break;
	}
	
	if (NewRotation >= MinRotate && NewRotation <= MaxRotate) {
		CurrentRotation = NewRotation;
		SetActorRelativeRotation(FRotator(0.0f, 0.0f, CurrentRotation));
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

void ATuningPegs::InitializeRotationRange(float Min, float Max)
{
	MinRotate = Min;
	MaxRotate = Max;
	Tolerance = 0.4f;  
	CurrentRotation = 0.0f;
	
	if (FMath::RandBool()) {
		TargetRotation = FMath::RandRange(1.5f, 3.5f);
	} else {
		TargetRotation = FMath::RandRange(6.5f, 8.5f);
	}

	RandomizeRotation();
}

void ATuningPegs::RandomizeRotation()
{
	CurrentRotation = FMath::RandRange(MinRotate, MaxRotate);
	SetActorRelativeRotation(FRotator(0.0f, 0.0f, CurrentRotation));
}

bool ATuningPegs::IsInCorrectPosition() const
{
	return FMath::Abs(CurrentRotation - TargetRotation) <= Tolerance;
}





