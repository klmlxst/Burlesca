// Copyright Uncertain Studios (c). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

class UInteractionInfo;
class UPauseMenu;
struct FInteractableObjectInfo;

UCLASS()
class BURLESCA_API AGameplayHUD : public AHUD
{
protected:

private:
	GENERATED_BODY()

public:
	AGameplayHUD();

	UPROPERTY(EditDefaultsOnly, Category = "User Widgets")
	TSubclassOf<UPauseMenu> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "User Widgets")
	TSubclassOf<UInteractionInfo> InteractionWidgetClass;

	bool bIsPauseMenuVisible;
	
	void DisplayPauseMenu();
	void HidePauseMenu();

	void ShowInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableObjectInfo* InteractableObjectInfo) const;
	void ShowHintInInteractionWidget(const FText HintText) const;
	void ClearHintInInteractionWidget() const;
	void ClearInteractionWidget() const;
	void HideInteractionWidget() const;

protected:
	UPROPERTY()
	UPauseMenu* PauseMenuWidget;

	UPROPERTY()
	UInteractionInfo* InteractionInfoWidget;
	
	virtual void BeginPlay() override;
	
};
