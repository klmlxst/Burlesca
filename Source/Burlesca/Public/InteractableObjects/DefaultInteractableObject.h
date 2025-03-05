// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Framework/DependencyInjection/Inject.h"
#include "GameFramework/Actor.h"
#include "DefaultInteractableObject.generated.h"

class AMainCharacter;
class USignalBus;
struct FInteractableObjectInfo;

UCLASS(Abstract)
class BURLESCA_API ADefaultInteractableObject : public AActor, public IInteractable, public IInject
{
	GENERATED_BODY()
	
public:
	ADefaultInteractableObject();
	
	virtual void StartFocus() override;
	virtual void StartSemiFocus() override;
	virtual void EndFocus() override;
	virtual void Interact() override;
	
	virtual FInteractableObjectInfo* GetInteractableObjectInfo() override;

	virtual void Inject(UDependencyContainer* Container) override;
	
protected:	
	UPROPERTY(EditAnywhere, Category="Interactivity Settings");
	FInteractableObjectInfo InteractableObjectInfo;
	
	UPROPERTY()
	USignalBus* SignalBus;

	UPROPERTY()
	AMainCharacter* MainCharacter;
	
protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
};
