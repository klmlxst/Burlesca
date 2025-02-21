// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhoneIsInHands);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhoneIsInPocket);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhoneFocusStateChanged, bool, bIsFocused);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHandIsOutOfFOV);

UENUM(Blueprintable)
enum class EPhoneAnimation : uint8
{
	None,
	PickUpFromPocket,
	PutDownInPocket,
	Focus,
	Unfocus,
	PutPhoneInWorld
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
	void PlayPhoneAnimation(EPhoneAnimation AnimType);

	UPROPERTY(BlueprintCallable)
	FOnPhoneIsInHands OnPhoneIsInHands;

	UPROPERTY(BlueprintCallable)
	FOnPhoneIsInPocket OnPhoneIsInPocket;

	UPROPERTY(BlueprintCallable)
	FOnPhoneFocusStateChanged OnPhoneFocusStateChanged;

	UPROPERTY(BlueprintCallable)
	FOnHandIsOutOfFOV OnHandIsOutOfFOV;
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

	UPROPERTY(BlueprintReadWrite)
	float RightArmAnimationWeight;
};
