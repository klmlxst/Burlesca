// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HUD/GameplayHUD.h"
#include "InteractableObjects/Interactable.h"
#include "TP_MainCharInteractionController.generated.h"

class UInteractionCaseController;
class IInteractable;
class UCameraComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;

struct FHitResult;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BURLESCA_API UTP_MainCharInteractionController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTP_MainCharInteractionController();
	void Init(UCameraComponent* camera);
	void SetupInput(UInputComponent* input);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UCameraComponent* MainCamera;

	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	AActor* CurrentInteractable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "InteractionSettings")
	uint16 InfoCastLength;

	UPROPERTY()
	UInteractionCaseController* InteractionController;
	
	void PerformInteractableCheck();
};
