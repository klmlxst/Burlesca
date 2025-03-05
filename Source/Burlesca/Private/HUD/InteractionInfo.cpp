// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InteractionInfo.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "HUD/CircularProgressBar.h"
#include "InteractableObjects/Interactable.h"

void UInteractionInfo::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInteractionInfo::NativeConstruct()
{
	Super::NativeConstruct();

	KeyToPressText->SetText(FText::FromString("Press [E] To Interact"));
}

void UInteractionInfo::UpdateWidget(const FInteractableObjectInfo* InteractableObjectInfo) const
{
	NameText->SetText(InteractableObjectInfo->Name);
	KeyToPressText->SetText(FText::FromString("Press [E] To Interact"));
	LockImage->SetVisibility(ESlateVisibility::Collapsed);
	
	switch (InteractableObjectInfo->InteractionType)
	{
		case EInteractableObjectType::CommonInteraction:
			break;
		
		case EInteractableObjectType::Hidden:
			KeyToPressText->SetText(FText::GetEmpty());
			NameText->SetText(FText::GetEmpty());
			break;
		
		case EInteractableObjectType::Pickup:
			KeyToPressText->SetText(FText::FromString("Press [E] To Pick Item Up"));
			break;
		
		case EInteractableObjectType::Putdown:
			NameText->SetText(FText::FromString(""));
			KeyToPressText->SetText(FText::FromString("Press [E] To Put Item Down"));
			break;
		
		case EInteractableObjectType::Other:
			break;
	}

	if(InteractableObjectInfo->ActivityState == EInteractableObjectActivityState::SemiActive)
	{
		LockImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInteractionInfo::ShowHintInInteractionWidget(const FText HintText) const
{
	SemiActiveHintText->SetText(HintText);
}

void UInteractionInfo::ClearWIdget()
{
	NameText->SetText(FText::GetEmpty());
	KeyToPressText->SetText(FText::GetEmpty());
	SemiActiveHintText->SetText(FText::GetEmpty());
	LockImage->SetVisibility(ESlateVisibility::Collapsed);
}
