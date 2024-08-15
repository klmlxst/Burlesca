// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterComponents/Interaction/InteractionCaseController.h"
#include "InteractableObjects/Interactable.h"
#include "HUD/GameplayHUD.h"

void UInteractionCaseController::Init(AGameplayHUD* Hud)
{
	HUD = Hud;
}

void UInteractionCaseController::InteractableFound(AActor* InteractableObject)
{
	if(CurrentInteractable)
	{
		TargetInteractable = CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	CurrentInteractable = InteractableObject;
	TargetInteractable = CurrentInteractable;

	FInteractableObjectInfo* Info = TargetInteractable->GetInteractableObjectInfo();

	switch(Info->ActivityState)
	{
		case EInteractableObjectActivityState::Active:
			TargetInteractable->StartFocus();
			HUD->ShowInteractionWidget();
			HUD->UpdateInteractionWidget(Info);
			break;
		
		case EInteractableObjectActivityState::SemiActive:
			TargetInteractable->StartSemiFocus();
			HUD->ShowInteractionWidget();
			HUD->UpdateInteractionWidget(Info);
			break;
			
		case EInteractableObjectActivityState::InActive:
			InteractableNotFound();
			break;
	}
}

void UInteractionCaseController::InteractableNotFound()
{
	if(CurrentInteractable)
	{
		if(IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}
	}
	
	HUD->HideInteractionWidget();
	HUD->ClearInteractionWidget();
	
	TargetInteractable = nullptr;
	CurrentInteractable = nullptr;
}

void UInteractionCaseController::InteractionCalled()
{
	if(CurrentInteractable)
	{
		if(IsValid(TargetInteractable.GetObject()))
		{
			FInteractableObjectInfo* Info = TargetInteractable->GetInteractableObjectInfo();

			switch(Info->ActivityState)
			{
				case EInteractableObjectActivityState::Active:
					TargetInteractable->Interact();
					break;
					
				case EInteractableObjectActivityState::SemiActive:
					if(!bIsHintShowed)
					{
						HUD->ShowHintInInteractionWidget(Info->HintText);
					}
					else
					{
						HUD->ClearHintInInteractionWidget();
					}
					break;
				
			case EInteractableObjectActivityState::InActive:
				break;
			}
		}
	}
}
