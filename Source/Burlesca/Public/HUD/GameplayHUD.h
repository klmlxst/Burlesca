// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/DependencyInjection/Inject.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

class USignalBus;
class UInteractionInfo;
class UPauseMenu;
struct FInteractableObjectInfo;

UCLASS()
class BURLESCA_API AGameplayHUD : public AHUD, public IInject
{
protected:

private:
	GENERATED_BODY()

public:
	AGameplayHUD();

	virtual void Inject(UDependencyContainer* Container) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "User Widgets")
	TSubclassOf<UPauseMenu> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Widgets")
	TSubclassOf<UInteractionInfo> InteractionWidgetClass;
	
	bool bIsPauseMenuVisible;

	UFUNCTION()
	void DisplayPauseMenu();

	UFUNCTION()
	void HidePauseMenu();

	
	UFUNCTION()
	void ShowInteractionWidget();

	UFUNCTION()
	void HideInteractionWidget();
	
	void UpdateInteractionWidget(const FInteractableObjectInfo* InteractableObjectInfo) const;

	UFUNCTION()
	void ClearInteractionWidget();
	
	void ShowHintInInteractionWidget(const FText HintText) const;

protected:
	UPROPERTY()
	UPauseMenu* PauseMenuWidget;

	UPROPERTY()
	UInteractionInfo* InteractionInfoWidget;

	UPROPERTY()
	USignalBus* SignalBus;
	
	virtual void BeginPlay() override;
	void SubscribeEvents();
};
