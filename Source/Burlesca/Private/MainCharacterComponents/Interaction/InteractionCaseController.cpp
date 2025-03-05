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
			HUD->UpdateInteractionWidget(Info);
			break;
		
		case EInteractableObjectActivityState::SemiActive:
			TargetInteractable->StartSemiFocus();
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
			HUD->ClearInteractionWidget();
		}
	}
	
	TargetInteractable = nullptr;
	CurrentInteractable = nullptr;

	bIsHintShowed = false;
}

void UInteractionCaseController::InteractionCalled()
{
	if(CurrentInteractable)
	{
		if(IsValid(TargetInteractable.GetObject()))
		{
			FInteractableObjectInfo* Info = TargetInteractable->GetInteractableObjectInfo();

			if(Info->bSetOutlineOffOnInteraction)
			{
				TargetInteractable->EndFocus();
			}
			
			switch(Info->ActivityState)
			{
				case EInteractableObjectActivityState::Active:
					TargetInteractable->Interact();
					break;
					
				case EInteractableObjectActivityState::SemiActive:
					if(!bIsHintShowed)
					{
						HUD->ClearInteractionWidget();
						HUD->ShowHintInInteractionWidget(Info->HintText);
					}
					break;
				
			case EInteractableObjectActivityState::InActive:
				break;
			}
		}
	}
}
