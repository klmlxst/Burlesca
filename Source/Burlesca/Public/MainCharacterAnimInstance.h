// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhoneIsInHands);

UENUM(Blueprintable)
enum class EPhoneAnimationType : uint8
{
	PickUpFromPocket,
	HoldInHands,
	PutDownInPocket,
};

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

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPhoneAnimation(EPhoneAnimationType AnimType);

	UPROPERTY(BlueprintAssignable)
	FOnPhoneIsInHands OnPhoneIsInHands;
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
