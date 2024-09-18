// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatScreen.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UChatScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupInput(UEnhancedInputComponent* input);

	void OpenApplication();
	void CloseApplication();
	void ActivateApplication();
	void DeactivateApplication();
};
