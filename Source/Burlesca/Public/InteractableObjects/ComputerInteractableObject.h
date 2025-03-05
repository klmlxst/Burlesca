// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects/DefaultInteractableObject.h"
#include "ComputerInteractableObject.generated.h"

class UComputerScreen;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class BURLESCA_API AComputerInteractableObject : public ADefaultInteractableObject
{
	GENERATED_BODY()
public:
	AComputerInteractableObject();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* ComputerScreenWidgetComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UComputerScreen> ComputerScreenClass;

	UPROPERTY(VisibleDefaultsOnly)
	UComputerScreen* ComputerScreenWidget;

	UPROPERTY(EditAnywhere)
	AActor* Actor;
	
	void BeginPlay() override;

	virtual void Interact() override;
	
};
