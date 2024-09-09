// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"

#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(MainCharacter == nullptr)
	{
		return;
	}

	CharacterForwardMovingSpeed = MainCharacter->GetForwardMovementSpeedRelativeToMax();
	CharacterRightMovingSpeed = MainCharacter->GetRightMovementSpeedRelativeToMax();

	if(CharacterForwardMovingSpeed == 0 && CharacterRightMovingSpeed == 0)
	{
		bIsCharacterMoving = false;
	}
	else
	{
		bIsCharacterMoving = true;
	}
}

void UMainCharacterAnimInstance::Init(USignalBus* signalBus)
{
	SignalBus = signalBus;
	check(SignalBus);

	
}
