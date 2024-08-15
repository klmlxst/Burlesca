// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacterComponents/TP_MainCharMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

UTP_MainCharMovementComponent::UTP_MainCharMovementComponent()
{
	
}

void UTP_MainCharMovementComponent::SetupInput(UInputComponent* input)
{
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(input);
	
	enhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &UTP_MainCharMovementComponent::MoveForward);
	enhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &UTP_MainCharMovementComponent::MoveRight);
}

void UTP_MainCharMovementComponent::ChangePossesionState(bool targetState)
{
		IsPossesedByCutscene = targetState;
}

void UTP_MainCharMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	check(Owner);
}

void UTP_MainCharMovementComponent::MoveForward(const FInputActionValue& Value)
{
	if(!IsPossesedByCutscene)
	{
		Owner->AddMovementInput(Owner->GetActorForwardVector(),Value.Get<float>());
	}
}

void UTP_MainCharMovementComponent::MoveRight(const FInputActionValue& Value)
{
	if(!IsPossesedByCutscene)
	{
		Owner->AddMovementInput(Owner->GetActorRightVector(),Value.Get<float>());	
	}
}
