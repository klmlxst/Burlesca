// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/MobilePhoneController.h"

#include "EnhancedInputComponent.h"
#include "MainCharacter.h"
#include "MobilePhone/MobilePhone.h"

UMobilePhoneController::UMobilePhoneController()
{
	PhoneSituation = EPhoneSituation::InPocket;
}

void UMobilePhoneController::Init(AMobilePhone* mobilePhone, AMainCharacter* mainCharacter)
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
			GetWorld()->GetTimerManager().SetTimer(ChangePhoneSituationTimerHandle, this, &UMobilePhoneController::TakePhoneInHands,0.6f);
			break;
			
		case EPhoneSituation::InHands:
			bCanChangePhoneSituation = false;
			GetWorld()->GetTimerManager().SetTimer(ChangePhoneSituationTimerHandle, this, &UMobilePhoneController::PutPhoneInPocket,0.6f);
			break;
		}
	}
}

void UMobilePhoneController::TakePhoneInHands()
{
	bCanChangePhoneSituation = true;
	PhoneSituation = EPhoneSituation::InHands;
	MobilePhone->SetActorLocation(MobilePhone->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f));
}

void UMobilePhoneController::PutPhoneInPocket()
{
	bCanChangePhoneSituation = true;
	PhoneSituation = EPhoneSituation::InPocket;
	MobilePhone->SetActorLocation(MobilePhone->GetActorLocation() - FVector(0.0f, 0.0f, 100.0f));
}

void UMobilePhoneController::ChangePhoneFocusState()
{
}
