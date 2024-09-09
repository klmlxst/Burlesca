// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

class USignalBus;
class AMainCharacter;
/**
 * 
 */
UCLASS()
class BURLESCA_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void Init(USignalBus* signalBus);
protected:
	UPROPERTY(BlueprintReadOnly)
	AMainCharacter* MainCharacter;

	UPROPERTY()
	USignalBus* SignalBus;
	
	UPROPERTY(BlueprintReadOnly)
	float CharacterForwardMovingSpeed;
	
	UPROPERTY(BlueprintReadOnly)
	float CharacterRightMovingSpeed;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCharacterMoving;
};
