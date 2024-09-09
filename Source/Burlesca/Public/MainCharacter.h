// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputSetupable.h"
#include "Framework/DependencyInjection/Inject.h"
#include "GameFramework/Character.h"
#include "MainCharacterComponents/TP_MainCharacterCameraController.h"
#include "MainCharacterComponents/TP_MainCharMovementComponent.h"
#include "MainCharacter.generated.h"

class UMainCharacterAnimInstance;
class AMobilePhone;
class UDependencyContainer;
class IInteractable;
class UTP_MainCharInteractionController;
class UTP_MainCharacterCameraController;
class UTP_MainCharMovementComponent;
class UInputMappingContext;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class BURLESCA_API AMainCharacter : public ACharacter, public IInject, public IInputSetupable
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void SetupInput(UEnhancedInputComponent* InputComponent) override;
	virtual void Inject(UDependencyContainer* Container) override;
	
	UFUNCTION()
	void StopAllPlayerServicies();

	UFUNCTION()
	void PlayAllPlayerServicies();

	UFUNCTION()
	UMainCharacterAnimInstance* CreateAnimInstance(UClass* AnimInstanceClass);
	
	UFUNCTION(BlueprintCallable)
	float GetForwardMovementSpeedRelativeToMax() const { return MovementController->GetForwardMovementSpeedRelativeToMax(); }

	UFUNCTION(BlueprintCallable)
	float GetRightMovementSpeedRelativeToMax() const { return MovementController->GetRightMovementSpeedRelativeToMax(); }
	
	void MoveCameraTo(AActor* PositionActor, float MovementDuration, bool bIsMovingFromCharacter, bool bIsMovingToCharacter = false) const;
	void MoveCameraTo(FVector PositionVector, FRotator RotationVector, float MovementDuration, bool bIsMovingFromCharacter, bool bIsMovingToCharacter = false) const;
	void ReturnCameraToCharacter(float MovementDuration) const;

	AMobilePhone* GetMobilePhone() const;
	
protected:	
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

	UPROPERTY(EditAnywhere, Category = "ChildActor")
	UChildActorComponent* MobilePhone;
	
	UPROPERTY(VisibleAnywhere, Category = HUD)
	AGameplayHUD* HUD;

	UPROPERTY()
	USignalBus* SignalBus;
	
	void ComponentsInitialization();
	void SubscribeEvents();

	UFUNCTION()
	void ActivateStaticMesh() { ArmsMesh->SetVisibility(true); }
	
	UFUNCTION()
	void DeactivateStaticMesh() { ArmsMesh->SetVisibility(false); }
};
