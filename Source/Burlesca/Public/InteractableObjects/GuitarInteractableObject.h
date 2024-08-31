// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultInteractableObject.h"
#include "GuitarInteractableObject.generated.h"

class UGuitarSetupController;


UCLASS()
class BURLESCA_API AGuitarInteractableObject : public ADefaultInteractableObject
{
	GENERATED_BODY()

public:
	AGuitarInteractableObject();
	virtual void Inject(UDependencyContainer* Container) override;

protected:
	virtual void BeginPlay() override;
	virtual void Interact() override;

	UPROPERTY()
	UGuitarSetupController* GuitarSetupController;
	
};
