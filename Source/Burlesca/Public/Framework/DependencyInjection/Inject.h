﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DependencyContainer.h"
#include "UObject/Interface.h"
#include "Inject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BURLESCA_API IInject
{
	GENERATED_BODY()

public:
	virtual void Inject(UDependencyContainer* Container) = 0;
};
