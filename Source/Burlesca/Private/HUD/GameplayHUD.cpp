// Copyright Uncertain Studios (c). All Rights Reserved.


#include "HUD/GameplayHUD.h"

#include "Framework/SignalBus.h"
#include "HUD/InteractionInfo.h"
#include "HUD/PauseMenu.h"

AGameplayHUD::AGameplayHUD()
{
}

void AGameplayHUD::Inject(UDependencyContainer* Container)
{
	SignalBus = Container->Resolve<USignalBus>();

	SubscribeEvents();
}

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();
	
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
		InteractionInfoWidget->ClearWIdget();

		ShowInteractionWidget();
	}

	check(InteractionInfoWidget);
	check(PauseMenuWidget);
}

void AGameplayHUD::SubscribeEvents()
{
	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraReturnedToCharacter.AddDynamic(this, &AGameplayHUD::ShowInteractionWidget);
	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraMovedOutFromCharacter.AddDynamic(this, &AGameplayHUD::ClearInteractionWidget);
	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraMovedOutFromCharacter.AddDynamic(this, &AGameplayHUD::HideInteractionWidget);
	
	SignalBus->GetGlobalGameEventsContainer()->OnGamePaused.AddDynamic(this, &AGameplayHUD::DisplayPauseMenu);
	SignalBus->GetGlobalGameEventsContainer()->OnGameUnpaused.AddDynamic(this, &AGameplayHUD::HidePauseMenu);
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

void AGameplayHUD::ShowInteractionWidget() 
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameplayHUD::HideInteractionWidget() 
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AGameplayHUD::UpdateInteractionWidget(const FInteractableObjectInfo* InteractableObjectInfo) const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->UpdateWidget(InteractableObjectInfo);
	}
}

void AGameplayHUD::ClearInteractionWidget() 
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->ClearWIdget();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Clear widget"));
}

void AGameplayHUD::ShowHintInInteractionWidget(const FText HintText) const
{
	if(InteractionInfoWidget)
	{
		InteractionInfoWidget->ShowHintInInteractionWidget(HintText);
	}
}
