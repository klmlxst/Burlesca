// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TuningPegs.generated.h"


class UStaticMeshComponent;

UENUM()
enum class ERotationDirection:uint8
{
	Left,
	Right
};

UCLASS()
class BURLESCA_API ATuningPegs : public AActor
{
	GENERATED_BODY()

public:
	ATuningPegs();
	void Select();
	void Deselect();
	void Rotate(ERotationDirection RotationDirection);
	void SetComplete();
	float GetCurrentRotation() const;
	
	void InitializeRotationRange(float Min, float Max);
	void RandomizeRotation();
	bool IsInCorrectPosition() const;
	
protected:
	UPROPERTY(EditInstanceOnly)
	float RotationSpeed = 0.0f;	

	UPROPERTY(EditInstanceOnly)
	float CurrentRotation;

	UPROPERTY(EditInstanceOnly)
	float TargetRotation;

	UPROPERTY(EditInstanceOnly)
	float MinRotate = 0.0f;

	UPROPERTY(EditInstanceOnly)
	float MaxRotate = 10.0f;

	UPROPERTY(EditInstanceOnly)
	float Tolerance;
		
	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* StaticMeshComponent;
	
};
