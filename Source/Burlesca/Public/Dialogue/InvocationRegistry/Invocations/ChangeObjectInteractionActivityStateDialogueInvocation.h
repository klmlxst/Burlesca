// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dialogue/InvocationRegistry/DialogueInvocation.h"
#include "UObject/Object.h"
#include "ChangeObjectInteractionActivityStateDialogueInvocation.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UChangeObjectInteractionActivityStateDialogueInvocation : public UObject, public IDialogueInvocation
{
	GENERATED_BODY()

public:
	virtual void InitDependenciesFromDIContainer(UDependencyContainer* container) override;
	virtual void Invoke(FDialogueInvocationParams conditionParams) override;

protected:
};
