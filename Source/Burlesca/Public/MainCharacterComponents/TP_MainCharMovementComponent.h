// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_MainCharMovementComponent.generated.h"

struct FInputActionValue;

class UInputComponent;
class UInputMappingContext;
class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BURLESCA_API UTP_MainCharMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTP_MainCharMovementComponent();
	void SetupInput(UInputComponent* input);

	void ChangePossesionState(bool targetState);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ACharacter* Owner;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;

	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);

	bool IsPossesedByCutscene;
};
