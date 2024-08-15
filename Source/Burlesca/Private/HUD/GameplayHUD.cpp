// Copyright Uncertain Studios (c). All Rights Reserved.


#include "HUD/GameplayHUD.h"
#include "HUD/InteractionInfo.h"
#include "HUD/PauseMenu.h"

AGameplayHUD::AGameplayHUD()
{
}

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("HUD Initialized"));
	
	if(PauseMenuClass)
	{
		PauseMenuWidget = CreateWidget<UPauseMenu>(GetWorld(),PauseMenuClass);
		PauseMenuWidget->AddToViewport(5);
		PauseMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(InteractionWidgetClass)
	{
		InteractionInfoWidget = CreateWidget<UInteractionInfo>(GetWorld(),InteractionWidgetClass);
		InteractionInfoWidget->AddToViewport(-1);
		InteractionInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	check(InteractionInfoWidget);
	check(PauseMenuWidget);
}

void AGameplayHUD::DisplayPauseMenu()
{
	if(PauseMenuWidget)
	{
		bIsPauseMenuVisible = true;
		PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameplayHUD::HidePauseMenu()
{
	if(PauseMenuWidget)
	{
		bIsPauseMenuVisible = false;
		PauseMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AGameplayHUD::ShowInteractionWidget() const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameplayHUD::UpdateInteractionWidget(const FInteractableObjectInfo* InteractableObjectInfo) const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->UpdateWidget(InteractableObjectInfo);
	}
}

void AGameplayHUD::ShowHintInInteractionWidget(const FText HintText) const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->ShowHintInInteractionWidget(HintText);
	}
}

void AGameplayHUD::ClearHintInInteractionWidget() const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->ClearHintInInteractionWidget();
	}
}

void AGameplayHUD::ClearInteractionWidget() const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->ClearWIdget();
	}
}

void AGameplayHUD::HideInteractionWidget() const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
