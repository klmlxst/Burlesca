// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UENUM()
enum class EInteractableObjectType : uint8
{
	CommonInteraction UMETA(DisplayName = "Default"),
	Hidden UMETA(DisplayName = "Hidden"),
	Pickup UMETA(DisplayName = "Pick Up"),
	Putdown UMETA(DisplayName = "Put Down")
};

UENUM()
enum class EInteractableObjectActivityState : uint8
{
	Active UMETA(DisplayName = "Active"),
	SemiActive UMETA(DisplayName = "Semi Active"),
	InActive UMETA(DisplayName = "Inactive")
};

USTRUCT()
struct FInteractableObjectInfo
{
	GENERATED_USTRUCT_BODY()

	FInteractableObjectInfo():
	InteractionType(EInteractableObjectType::CommonInteraction),
	ActivityState(EInteractableObjectActivityState::Active),
	Name(FText::GetEmpty()),
	HintText(FText::GetEmpty()) {};

	UPROPERTY(EditAnywhere)
	EInteractableObjectType InteractionType;

	UPROPERTY(EditAnywhere)
	EInteractableObjectActivityState ActivityState;
	
	UPROPERTY(EditAnywhere, meta = (ToolTip = "Will not be shown if object is <InActive>"))
	FText Name;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Will be shown if object is <SemiActive>, will appear on interaction try"))
	FText HintText;
};

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class BURLESCA_API IInteractable
{
	GENERATED_BODY()
	
public:	
	virtual void StartFocus() = 0;
	virtual void StartSemiFocus() = 0;
	virtual void EndFocus() = 0;
	virtual void Interact() = 0;
	
	virtual FInteractableObjectInfo* GetInteractableObjectInfo() = 0;
};
