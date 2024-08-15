// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionCaseController.generated.h"

class IInteractable;
class AGameplayHUD;

UCLASS()
class BURLESCA_API UInteractionCaseController : public UObject
{
	GENERATED_BODY()

public:
	void Init(AGameplayHUD* Hud);

	void InteractableFound(AActor* InteractableObject);
	void InteractableNotFound();

	void InteractionCalled();
	
private:

	UPROPERTY()
	AGameplayHUD* HUD;

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	TScriptInterface<IInteractable> TargetInteractable;

	bool bIsHintShowed = false;
};
