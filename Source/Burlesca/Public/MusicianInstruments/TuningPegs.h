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
	
	void InitializeRotationRange();
	bool IsTuned() const;

	virtual void BeginPlay() override;
	
protected:

	UFUNCTION()
	void SetIsNotRotating() { bIsRotating = false; }

	UFUNCTION()
	void UpdateRelativeRotationViaCurrentRotationValue();
	
	UPROPERTY()
	FTimerHandle RotationReload;
	
	UPROPERTY(EditInstanceOnly)
	bool bIsTuned = false;
	
	UPROPERTY(EditInstanceOnly)
	float RotationSpeed = 0.0f;	

	UPROPERTY()
	float CurrentRotation = 0.0f;

	UPROPERTY()
	float TargetRotation = 5.0f;

	UPROPERTY(EditInstanceOnly)
	float MinRotation = 0.0f;

	UPROPERTY(EditInstanceOnly)
	float MaxRotation = 10.0f;
		
	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* StaticMeshComponent;

	bool bIsRotating = false;
	
};
