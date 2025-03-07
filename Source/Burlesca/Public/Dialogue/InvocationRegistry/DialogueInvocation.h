// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogueInvocation.generated.h"

class UDependencyContainer;
struct FDialogueInvocationParams;

UINTERFACE()
class UDialogueInvocation : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BURLESCA_API IDialogueInvocation
{
	GENERATED_BODY()

public:
	virtual void Invoke(FDialogueInvocationParams conditionParams) = 0;
	virtual void InitDependenciesFromDIContainer(UDependencyContainer* container) = 0;
};
