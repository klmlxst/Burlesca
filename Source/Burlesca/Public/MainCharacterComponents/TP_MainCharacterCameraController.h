// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_MainCharacterCameraController.generated.h"

class UCameraComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BURLESCA_API UTP_MainCharacterCameraController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTP_MainCharacterCameraController();
	void Init(UCameraComponent* camera);
	void SetupInput(UInputComponent* input);

	void ChangePossesionState(bool targetState);
	
protected:
	virtual void BeginPlay() override;

private:
	ACharacter* Owner;

	UPROPERTY()
	UCameraComponent* MainCamera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookXAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookYAction;

	void LookUp(const FInputActionValue& Value);
	void LookRight(const FInputActionValue& Value);

	bool IsPossesedByCutscene;
};
