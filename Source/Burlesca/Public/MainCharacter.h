// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class IInteractable;
class UTP_MainCharInteractionController;
class UTP_MainCharacterCameraController;
class UTP_MainCharMovementComponent;
class UInputMappingContext;
class UCameraComponent;
class USkeletalMeshComponent;
class UInputComponent;

UCLASS()
class BURLESCA_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, Category = CameraController)
	UTP_MainCharacterCameraController* CameraController;

	UPROPERTY(EditAnywhere, Category = MovementController)
	UTP_MainCharMovementComponent* MovementController;

	UPROPERTY(EditAnywhere, Category = MovementController)
	UTP_MainCharInteractionController* InteractionController;
	
	UPROPERTY(EditAnywhere, Category = CameraController)
	UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere, Category = Mesh)
	USkeletalMeshComponent* ArmsMesh;

	UFUNCTION(meta = (Inject))
	void Construct();
	
	void ComponentsInitialization();
	void ControllerComponentsSetup();

};
