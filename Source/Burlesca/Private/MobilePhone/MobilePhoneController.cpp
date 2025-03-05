// Fill out your copyright notice in the Description page of Project Settings.

#include "MobilePhone/MobilePhoneController.h"
#include "EnhancedInputComponent.h"
#include "MainCharacter.h"
#include "MobilePhone/MobilePhone.h"
#include "MobilePhone/MobilePhoneEnums.h"

UMobilePhoneController::UMobilePhoneController()
{
	PhoneSituation = EPhoneSituation::InPocket;
}

void UMobilePhoneController::Init()
{
	SubscribeEvents();
}

void UMobilePhoneController::Inject(UDependencyContainer* Container)
{
	MainCharacter = Container->Resolve<AMainCharacter>();
	check(MainCharacter)

	MobilePhone = Container->Resolve<AMobilePhone>();
	check(MobilePhone)

	AnimInstance = Container->Resolve<UMainCharacterAnimInstance>();
	check(AnimInstance)
	
	PlayerController = Container->Resolve<ABurlescaPlayerController>();
}

void UMobilePhoneController::InitInputActions(UInputAction* takePhoneInOrOutOfHandsAction, UInputAction* focusInOutAction)
{
	TakePhoneInOrOutOfHandsAction = takePhoneInOrOutOfHandsAction;
	FocusInOutAction = focusInOutAction;
}

void UMobilePhoneController::SetupInput(UEnhancedInputComponent* enhancedInputComponent)
{
	enhancedInputComponent->BindAction(TakePhoneInOrOutOfHandsAction, ETriggerEvent::Started, this, &UMobilePhoneController::ChoosePhoneTakeOrPut);
	enhancedInputComponent->BindAction(FocusInOutAction, ETriggerEvent::Started, this, &UMobilePhoneController::OnPhoneFocusStateChangeCalled);
}

void UMobilePhoneController::SubscribeEvents()
{
	AnimInstance->OnPhoneIsInHands.AddDynamic(this, &UMobilePhoneController::OnPhonePickedUpFromPocket);
	AnimInstance->OnPhoneIsInPocket.AddDynamic(this, &UMobilePhoneController::OnPhonePutDownToPocket);
	AnimInstance->OnPhoneFocusStateChanged.AddDynamic(this, &UMobilePhoneController::OnPhoneFocusStateChanged);
	AnimInstance->OnHandIsOutOfFOV.AddDynamic(this, &UMobilePhoneController::SwitchPhoneVisibility);
}

void UMobilePhoneController::ChoosePhoneTakeOrPut() 
{
	if(bCanChangePhoneSituation)
	{
		switch(PhoneSituation)
		{
		case EPhoneSituation::InPocket:
			bCanChangePhoneSituation = false;
			TakePhoneInHands();
			break;
				
		case EPhoneSituation::InHands:
			bCanChangePhoneSituation = false;
			PutPhoneInPocket();
			break;
		}
	}
}

void UMobilePhoneController::PutPhoneInPocket()
{
	MobilePhone->SetPowerState(false);
	AnimInstance->PlayPhoneAnimation(EPhoneAnimation::PutDownInPocket);
	MainCharacter->PlayAllPlayerServicies();
}

void UMobilePhoneController::OnPhonePickedUpFromPocket()
{
	PhoneSituation = EPhoneSituation::InHands;
	PowerPhoneOn();
	ResetCanChangePhoneSituation();
}

void UMobilePhoneController::OnPhonePutDownToPocket()
{
	PhoneSituation = EPhoneSituation::InPocket;
	ResetCanChangePhoneSituation();
}

void UMobilePhoneController::OnPhoneFocusStateChanged(bool bIsFocused)
{
	UE_LOG(LogTemp, Display, TEXT("OnPhoneFocusStateChanged , isFocused = %d"), bIsFocused);
	
	bIsPhoneFocused = bIsFocused;
	bCanChangePhoneFocusState = true;
	bCanChangePhoneSituation = true;

	if(!bIsFocused)
	{
		MainCharacter->PlayAllPlayerServicies();
		PlayerController->HideCursor();
	}
	else
	{
		MobilePhone->OnPhoneFocused();
		PlayerController->ShowCursor();
	}
}

void UMobilePhoneController::SwitchPhoneVisibility()
{
	switch (PhoneSituation)
	{
		case EPhoneSituation::InHands:
			MobilePhone->SetVisibility(true);
		break;
		
		case EPhoneSituation::InPocket:
			MobilePhone->SetVisibility(false);
		break;
	}
}

void UMobilePhoneController::OnPhoneFocusStateChangeCalled()
{
	if(PhoneSituation == EPhoneSituation::InHands && bCanChangePhoneFocusState && bCanChangePhoneSituation)
	{
		switch(bIsPhoneFocused)
		{
			case true:
				AnimInstance->PlayPhoneAnimation(EPhoneAnimation::Unfocus);
				bCanChangePhoneFocusState = false;
				bCanChangePhoneSituation = false;
				MobilePhone->OnPhoneUnfocused();
			break;
				
			case false:
				AnimInstance->PlayPhoneAnimation(EPhoneAnimation::Focus);
				bCanChangePhoneFocusState = false;
				bCanChangePhoneSituation = false;
				MainCharacter->StopAllPlayerServicies();
			break;
		}
	}
}

void UMobilePhoneController::PowerPhoneOn()
{
	MobilePhone->SetPowerState(true);
}






void UMobilePhoneController::PutPhoneInTheWorld(AActor* situationActor)
{
}

void UMobilePhoneController::TakePhoneFromTheWorld()
{
}

void UMobilePhoneController::SelectViewedApplication(EPhoneApplication phoneApplication)
{
}