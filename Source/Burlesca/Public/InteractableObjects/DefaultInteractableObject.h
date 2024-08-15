// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "DefaultInteractableObject.generated.h"

struct FInteractableObjectInfo;

UCLASS(Abstract)
class BURLESCA_API ADefaultInteractableObject : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	ADefaultInteractableObject();
	
	virtual void StartFocus() override;
	virtual void StartSemiFocus() override;
	virtual void EndFocus() override;
	virtual void Interact() override;
	
	virtual FInteractableObjectInfo* GetInteractableObjectInfo() override;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditInstanceOnly)
	FInteractableObjectInfo InteractableObjectInfo;
};
