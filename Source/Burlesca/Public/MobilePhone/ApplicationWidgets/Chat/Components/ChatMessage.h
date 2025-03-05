// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Dialogue/DialogueMessage.h"
#include "ChatMessage.generated.h"

/**
 * 
 */
UCLASS()
class BURLESCA_API UChatMessage : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(FText message, EMessageType messageType)
	{
		MessageTextBlock->SetText(message);
	}
	
protected:
	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UTextBlock* MessageTextBlock;

	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UBorder* BackgroundBorder;
};
