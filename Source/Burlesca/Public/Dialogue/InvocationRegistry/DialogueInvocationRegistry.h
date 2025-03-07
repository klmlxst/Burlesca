// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/DependencyInjection/Inject.h"
#include "UObject/Object.h"
#include "DialogueInvocationRegistry.generated.h"


struct FDialogueInvocationParams;
enum class EDialogueInvocationType : uint16;

UCLASS()
class BURLESCA_API UDialogueInvocationRegistry : public UObject, public IInject
{
	GENERATED_BODY()

public:
	void virtual Inject(UDependencyContainer* Container) override;
	void Invoke(EDialogueInvocationType conditionType, FDialogueInvocationParams params);
	
	UPROPERTY()
	TMap<EDialogueInvocationType, UObject*> Invocations;
};
