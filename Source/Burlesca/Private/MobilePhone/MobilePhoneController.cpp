// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/MobilePhoneController.h"

#include "EnhancedInputComponent.h"
#include "MainCharacter.h"
#include "MainCharacterAnimInstance.h"
#include "MobilePhone/MobilePhone.h"

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

	AnimInstance->OnPhoneIsInHands.AddDynamic(this, &UMobilePhoneController::PowerPhoneOn);
}

void UMobilePhoneController::InitInputActions(UInputAction* takePhoneInOrOutOfHandsAction)
{
	TakePhoneInOrOutOfHandsAction = takePhoneInOrOutOfHandsAction;
}

void UMobilePhoneController::SetupInput(UEnhancedInputComponent* enhancedInputComponent)
{
	enhancedInputComponent->BindAction(TakePhoneInOrOutOfHandsAction, ETriggerEvent::Started, this, &UMobilePhoneController::ChoosePhoneTakeOrPut);
}

void UMobilePhoneController::PutPhoneInTheWorld(AActor* situationActor)
{
}

void UMobilePhoneController::TakePhoneFromTheWorld()
{
}

void UMobilePhoneController::SelectViewedApplication(EPhoneApplication PhoneApplication)
{
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
	bCanChangePhoneSituation = true;
	PhoneSituation = EPhoneSituation::InHands;
	AnimInstance->PlayPhoneAnimation(EPhoneAnimation::PickUpFromPocket);
}

void UMobilePhoneController::PutPhoneInPocket()
{
	bCanChangePhoneSituation = true;
	PhoneSituation = EPhoneSituation::InPocket;
	MobilePhone->SetPowerState(false);
	AnimInstance->PlayPhoneAnimation(EPhoneAnimation::PutDownInPocket);
}

void UMobilePhoneController::ChangePhoneFocusState()
{
}
