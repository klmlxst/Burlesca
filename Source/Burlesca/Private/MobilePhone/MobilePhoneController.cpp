// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/MobilePhoneController.h"

#include "EnhancedInputComponent.h"
#include "MainCharacter.h"
#include "MainCharacterAnimInstance.h"
#include "MobilePhone/MobilePhone.h"
#include "MobilePhone/MobilePhoneEnums.h"

UMobilePhoneController::UMobilePhoneController()
{
	PhoneSituation = EPhoneSituation::InPocket;
}

void UMobilePhoneController::Init(AMobilePhone* mobilePhone, AMainCharacter* mainCharacter, UMainCharacterAnimInstance* animInstance)
{
	MobilePhone = mobilePhone;
	if(MobilePhone == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Mobile phone is null in installer"));
	}

	MainCharacter = mainCharacter;
	if(MainCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Main character is null in installer"));
	}

	AnimInstance = animInstance;
	if(AnimInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Anim instance is null in installer"));
	}

	SubscribeEvents();
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

void UMobilePhoneController::PowerPhoneOn()
{
	MobilePhone->SetPowerState(true);
}

void UMobilePhoneController::SubscribeEvents()
{
	AnimInstance->OnPhoneIsInHands.AddDynamic(this, &UMobilePhoneController::PowerPhoneOn);
	AnimInstance->OnPhoneIsInHands.AddDynamic(this, &UMobilePhoneController::ResetCanChangePhoneSituation);
	AnimInstance->OnPhoneIsInPocket.AddDynamic(this, &UMobilePhoneController::ResetCanChangePhoneSituation);
	AnimInstance->OnPhoneFocusStateChanged.AddDynamic(this, &UMobilePhoneController::OnPhoneFocusStateChanged);
	AnimInstance->OnHandIsOutOfFOV.AddDynamic(this, &UMobilePhoneController::SwitchPhoneVisibility);
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

void UMobilePhoneController::TakePhoneInHands()
{
	bCanChangePhoneSituation = false;
	PhoneSituation = EPhoneSituation::InHands;
	AnimInstance->PlayPhoneAnimation(EPhoneAnimation::PickUpFromPocket);
}

void UMobilePhoneController::PutPhoneInPocket()
{
	bCanChangePhoneSituation = false;
	PhoneSituation = EPhoneSituation::InPocket;
	MobilePhone->SetPowerState(false);
	AnimInstance->PlayPhoneAnimation(EPhoneAnimation::PutDownInPocket);
	MainCharacter->PlayAllPlayerServicies();
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

void UMobilePhoneController::OnPhoneFocusStateChanged(bool bIsFocused)
{
	bIsPhoneFocused = bIsFocused;
	bCanChangePhoneFocusState = true;
	bCanChangePhoneSituation = true;

	if(!bIsFocused)
	{
		MainCharacter->PlayAllPlayerServicies();
	}
	else
	{
		MobilePhone->OnPhoneFocused();
	}
}
