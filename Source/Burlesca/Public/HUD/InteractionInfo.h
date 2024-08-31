// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionInfo.generated.h"

class UImage;
class UCircularProgressBar;
class UProgressBar;
class UTextBlock;
struct FInteractableObjectInfo;
class AMainCharacter;

UCLASS()
class BURLESCA_API UInteractionInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget|Owner Character")
	AMainCharacter* Owner;
	
	void UpdateWidget(const FInteractableObjectInfo* InteractableObjectInfo) const;
	void ClearWIdget();
	void ShowHintInInteractionWidget(const FText HintText) const;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget|Interaction Visualization")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget|Interaction Visualization")
	UTextBlock* SemiActiveHintText;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget|Interaction Visualization")
	UTextBlock* KeyToPressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget|Interaction Visualization")
	UImage* LockImage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget|Interaction Visualization")
	UImage* BulletImage;
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};
