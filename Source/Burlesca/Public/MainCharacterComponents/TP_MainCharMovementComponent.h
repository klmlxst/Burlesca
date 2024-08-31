// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_MainCharMovementComponent.generated.h"

struct FInputActionValue;

class UEnhancedInputComponent;
class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BURLESCA_API UTP_MainCharMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTP_MainCharMovementComponent();
	void SetupInput(UEnhancedInputComponent* input);

	void PlayService();
	void StopService();

	FORCEINLINE bool IsServiceStoped() const { return bIsServiceStoped; }
	
protected:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 1;
	
	UFUNCTION()
	void MoveForward(const FInputActionValue& Value);

	UFUNCTION()
	void MoveRight(const FInputActionValue& Value);

	bool bIsServiceStoped;
};
