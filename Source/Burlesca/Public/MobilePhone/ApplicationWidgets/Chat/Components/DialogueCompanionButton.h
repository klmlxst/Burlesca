// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Dialogue/DialogueCompanion.h"
#include "DialogueCompanionButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelected, EDialogueCompanion, companion);

UCLASS()
class BURLESCA_API UDialogueCompanionButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void ShowWidget() { SetVisibility(ESlateVisibility::Visible); } 
	void HideWidget() { SetVisibility(ESlateVisibility::Collapsed); }

	void IncreaseUnreadMessagesQuantity()
	{		
		UnreadMessagesQuantityBackground->SetVisibility(ESlateVisibility::Visible);
		UnreadMessagesQuantity++;
		UnreadMessagesQuantityText->SetText(FText::FromString(FString::FromInt(UnreadMessagesQuantity)));
	}

	void ResetUnreadMessagesQuantity()
	{
		UnreadMessagesQuantityText->SetText(FText::FromString(""));
		UnreadMessagesQuantityBackground->SetVisibility(ESlateVisibility::Collapsed);
		UnreadMessagesQuantity = 0;
	}
	
	FOnSelected OnSelected;
	
protected:
	UFUNCTION()
	void OnButtonClicked()
	{
		ResetUnreadMessagesQuantity();
		OnSelected.Broadcast(DialogueCompanion);
	}
	
	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UButton* Button;

	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UTextBlock* LastMessageText;

	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UTextBlock* UnreadMessagesQuantityText;

	UPROPERTY(meta=(BindWidget), EditDefaultsOnly, BlueprintReadWrite)
	UBorder* UnreadMessagesQuantityBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogueCompanion DialogueCompanion;

	int UnreadMessagesQuantity = 0;
};
