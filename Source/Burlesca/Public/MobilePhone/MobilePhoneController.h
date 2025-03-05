// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BurlescaPlayerController.h"
#include "MainCharacterAnimInstance.h"
#include "Framework/DependencyInjection/Inject.h"
#include "UObject/Object.h"
#include "MobilePhoneController.generated.h"

enum class EPhoneSituation : uint8;
enum class EPhoneApplication : uint8;
class UMainCharacterAnimInstance;
class AMainCharacter;
class UInputAction;
class UMobilePhoneScreen;
class AMobilePhone;

/**
 * 
 */
UCLASS()
class BURLESCA_API UMobilePhoneController : public UObject, public IInject
{
	GENERATED_BODY()
public:
	UMobilePhoneController();
	void Init();
	virtual void Inject(UDependencyContainer* Container) override;
	void InitInputActions(UInputAction* TakePhoneInOrOutOfHandsAction, UInputAction* focusInOutAction);
	void SetupInput(UEnhancedInputComponent* enhancedInputComponent);
	
	void PutPhoneInTheWorld(AActor* situationActor);
	void TakePhoneFromTheWorld();
	void SelectViewedApplication(EPhoneApplication PhoneApplication);
protected:
	/*  ---  Global Variables  ---  */

	UPROPERTY()
	ABurlescaPlayerController* PlayerController;
	
	UPROPERTY()
	AMobilePhone* MobilePhone;

	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	UMainCharacterAnimInstance* AnimInstance;

	/*  ---  Change Phone Situation  ---  */

	UFUNCTION()
	void ResetCanChangePhoneSituation() { bCanChangePhoneSituation = true; }

	UFUNCTION()
	void SwitchPhoneVisibility();
	
	EPhoneSituation PhoneSituation;
	bool bCanChangePhoneSituation = true;
	
	/*  ---  Phone Take In Hands  ---  */

	UPROPERTY()
	UInputAction* TakePhoneInOrOutOfHandsAction;

	UFUNCTION()
	void ChoosePhoneTakeOrPut();

	UFUNCTION()
	void TakePhoneInHands() { AnimInstance->PlayPhoneAnimation(EPhoneAnimation::PickUpFromPocket); }
	
	UFUNCTION()
	void PutPhoneInPocket();
	
	/*  ---  Phone Focus  ---  */

	UPROPERTY()
	UInputAction* FocusInOutAction;

	UFUNCTION()
	void OnPhoneFocusStateChangeCalled();

	UFUNCTION()
	void OnPhoneFocusStateChanged(bool bIsFocused);

	bool bIsPhoneFocused = false;
	bool bCanChangePhoneFocusState = true;
	
	/*  ---  Functions  ---  */
	
	UFUNCTION()
	void PowerPhoneOn();

	void SubscribeEvents();

	/*  ---  On Event Functions  ---  */

	UFUNCTION()	
	void OnPhonePickedUpFromPocket();

	UFUNCTION()
	void OnPhonePutDownToPocket();
};
