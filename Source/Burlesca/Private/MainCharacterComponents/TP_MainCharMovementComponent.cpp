// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacterComponents/TP_MainCharMovementComponent.h"

#include "EnhancedInputComponent.h"

UTP_MainCharMovementComponent::UTP_MainCharMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTP_MainCharMovementComponent::SetupInput(UEnhancedInputComponent* input)
{
	Owner = GetOwner();
	check(Owner);
	
	input->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &UTP_MainCharMovementComponent::StartAcceleratingForward);
	input->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &UTP_MainCharMovementComponent::StartAcceleratingRight);
	
	input->BindAction(MoveForwardAction, ETriggerEvent::Completed, this, &UTP_MainCharMovementComponent::StartDeacceleratingForward);
	input->BindAction(MoveRightAction, ETriggerEvent::Completed, this, &UTP_MainCharMovementComponent::StartDeacceleratingRight);

	input->BindAction(RunAction, ETriggerEvent::Started, this, &UTP_MainCharMovementComponent::StartRunning);
	input->BindAction(RunAction, ETriggerEvent::Completed, this, &UTP_MainCharMovementComponent::StopRunning);

	
}

void UTP_MainCharMovementComponent::StartAcceleratingForward(const FInputActionValue& Value)
{
	if(bIsServiceStoped)
	{
		CurrentForwardMovementDirection = 0;
		return;	
	}
	
	if(Value.Get<float>() == -1)
	{
		CurrentForwardMovementDirection = 2;
	}
	else if(Value.Get<float>() == 1)
	{
		CurrentForwardMovementDirection = 1;
	}
}

void UTP_MainCharMovementComponent::StartAcceleratingRight(const FInputActionValue& Value)
{
	if(bIsServiceStoped)
	{
		CurrentRightMovementDirection = 0;
		return;	
	}
	
	if(Value.Get<float>() == -1)
	{
		CurrentRightMovementDirection = 2;
	}
	else if(Value.Get<float>() == 1)
	{
		CurrentRightMovementDirection = 1;
	}
}

void UTP_MainCharMovementComponent::StartDeacceleratingForward()
{
	CurrentForwardMovementDirection = 0;
}

void UTP_MainCharMovementComponent::StartDeacceleratingRight()
{
	CurrentRightMovementDirection = 0;
}

void UTP_MainCharMovementComponent::StartRunning()
{
	float PreviousSpeed = MaxCharacterMovementSpeed;
	MaxCharacterMovementSpeed = RunSpeed;
	RunSpeed = PreviousSpeed;
}

void UTP_MainCharMovementComponent::StopRunning()
{
	float PreviousSpeed = RunSpeed;
	RunSpeed = MaxCharacterMovementSpeed;
	MaxCharacterMovementSpeed = PreviousSpeed;
}

void UTP_MainCharMovementComponent::UpdateForwardVelocity(float DeltaTime)
{
	switch(CurrentForwardMovementDirection)
	{
		case 1:
			if(CurrentForwardMovementSpeed < MaxCharacterMovementSpeed)
			{
				CurrentForwardMovementSpeed += MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
			else
			{
				CurrentForwardMovementSpeed -= MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
		break;

		case 0:
			if(CurrentForwardMovementSpeed > 0)
			{
				CurrentForwardMovementSpeed -= MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
				
				if(CurrentForwardMovementSpeed < 0)
				{
					CurrentForwardMovementSpeed = 0;
				}
			}
			else if(CurrentForwardMovementSpeed < 0)
			{
				CurrentForwardMovementSpeed += MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
				
				if(CurrentForwardMovementSpeed > 0)
				{
					CurrentForwardMovementSpeed = 0;
				}
			}
		break;

		case 2:
			if(CurrentForwardMovementSpeed > MaxCharacterMovementSpeed * -1)
			{
				CurrentForwardMovementSpeed -= MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
			else
			{
				CurrentForwardMovementSpeed += MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
		break;
			
	}
}

void UTP_MainCharMovementComponent::UpdateRightVelocity(float DeltaTime)
{
	switch(CurrentRightMovementDirection)
	{
		case 1:
			if(CurrentRightMovementSpeed < MaxCharacterMovementSpeed)
			{
				CurrentRightMovementSpeed += MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
			else
			{
				CurrentRightMovementSpeed -= MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
		break;

		case 0:
			if(CurrentRightMovementSpeed > 0)
			{
				CurrentRightMovementSpeed -= MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
				
				if(CurrentRightMovementSpeed < 0)
				{
					CurrentRightMovementSpeed = 0;
				}
			}
			else if(CurrentRightMovementSpeed < 0)
			{
				CurrentRightMovementSpeed += MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
				
				if(CurrentRightMovementSpeed > 0)
				{
					CurrentRightMovementSpeed = 0;
				}
			}
		break;

		case 2:
			if(CurrentRightMovementSpeed > MaxCharacterMovementSpeed * -1)
			{
				CurrentRightMovementSpeed -= MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
			else
			{
				CurrentRightMovementSpeed += MaxCharacterMovementSpeed * AccelerationChangeSpeed * DeltaTime;
			}
		break;
	}
}

void UTP_MainCharMovementComponent::PlayService()
{
	bIsServiceStoped = false;
}

void UTP_MainCharMovementComponent::StopService()
{
	bIsServiceStoped = true;
}

void UTP_MainCharMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	check(Owner);

	if(bIsServiceStoped)
	{
		CurrentForwardMovementSpeed = 0;
		CurrentRightMovementSpeed = 0;
	}
	
	UpdateForwardVelocity(DeltaTime);
	UpdateRightVelocity(DeltaTime);
	
	if(CurrentForwardMovementSpeed != 0)
	{
		FVector ForwardVector = Owner->GetActorForwardVector();
		FVector NewForwardLocation = Owner->GetActorLocation() + ForwardVector * CurrentForwardMovementSpeed * DeltaTime;
		Owner->SetActorLocation(NewForwardLocation, true);
	}

	if(CurrentRightMovementSpeed != 0)
	{
		FVector RightVector = Owner->GetActorRightVector();
		FVector NewRightLocation = Owner->GetActorLocation() + RightVector * CurrentRightMovementSpeed * DeltaTime;
		Owner->SetActorLocation(NewRightLocation, true);
	}
}

