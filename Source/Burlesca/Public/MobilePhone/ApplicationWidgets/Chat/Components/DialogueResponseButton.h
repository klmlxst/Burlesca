// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "NodeInfo/DialogueGraphResponseNodeInfo.h"
#include "Sections/MovieSceneLevelVisibilitySection.h"
#include "DialogueResponseButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResponseSelected, int, selectedResponseId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConditonTooltipShow, const FText&, tooltipText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConditonTooltipHide);

UCLASS()
class BURLESCA_API UDialogueResponseButton : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UDialogueGraphResponseNodeInfo* info, int id)
	{
		ResponseText->SetText(info->ResponseText);
		ResponseId = id;
		ResponseIdText->SetText(FText::FromString(FString::FromInt(id + 1) + TEXT(".")));
		bAreConditionsMet = info->bAreConditionsMet;
		
		if (!bAreConditionsMet)
		{
			ConditionTooltip = info->ConditionTooltip;
			LockedResponseImage->SetVisibility(ESlateVisibility::Visible);
			LockedResponseImage->SetIsEnabled(true);
		}
	}

	int GetResponseId() { return ResponseId; }
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnResponseSelected OnResponseSelected;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnConditonTooltipShow OnConditonTooltipShow;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnConditonTooltipHide OnConditonTooltipHide;
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ResponseText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ResponseIdText;

	UPROPERTY(meta=(BindWidget))
	UImage* LockedResponseImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ResponseId;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bAreConditionsMet = true;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText ConditionTooltip = FText::FromString("");
};
