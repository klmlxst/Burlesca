// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacterComponents/TP_MainCharMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

UTP_MainCharMovementComponent::UTP_MainCharMovementComponent()
{
	
}

void UTP_MainCharMovementComponent::SetupInput(UEnhancedInputComponent* input)
{
	Owner = GetOwner();
	check(Owner);
	
	input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &UTP_MainCharMovementComponent::MoveForward);
	input->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &UTP_MainCharMovementComponent::MoveRight);
}

void UTP_MainCharMovementComponent::PlayService()
{
	bIsServiceStoped = false;
}

void UTP_MainCharMovementComponent::StopService()
{
	bIsServiceStoped = true;
}

void UTP_MainCharMovementComponent::MoveForward(const FInputActionValue& Value)
{
	if(!bIsServiceStoped)
	{
		FVector ForwardVector = Owner->GetActorForwardVector();

		FVector NewLocation = Owner->GetActorLocation() + ForwardVector * MovementSpeed * Value.Get<float>();

		Owner->SetActorLocation(NewLocation);
	}
}

void UTP_MainCharMovementComponent::MoveRight(const FInputActionValue& Value)
{
	if(!bIsServiceStoped)
	{
		FVector RightVector = Owner->GetActorRightVector();

		FVector NewLocation = Owner->GetActorLocation() + RightVector * MovementSpeed * Value.Get<float>();

		Owner->SetActorLocation(NewLocation);
	}
}
