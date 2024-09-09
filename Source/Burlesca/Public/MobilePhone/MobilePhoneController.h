// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MobilePhoneController.generated.h"

class UMainCharacterAnimInstance;
class AMainCharacter;
class UInputAction;
class UMobilePhoneScreen;
class AMobilePhone;

UENUM()
enum class EPhoneApplication : uint8
{
	MainScreen,
	GuitarSetup,
	Chat
};

UENUM()
enum class EPhoneSituation : uint8
{
	InPocket,
	InHands,
	InWorld
};

/**
 * 
 */
UCLASS()
class BURLESCA_API UMobilePhoneController : public UObject
{
	GENERATED_BODY()
public:
	UMobilePhoneController();
	void Init(AMobilePhone* mobilePhone, AMainCharacter* mainCharacter, UMainCharacterAnimInstance* animInstance);
	void InitInputActions(UInputAction* TakePhoneInOrOutOfHandsAction);
	void SetupInput(UEnhancedInputComponent* enhancedInputComponent);
	
	void PutPhoneInTheWorld(AActor* situationActor);
	void TakePhoneFromTheWorld();
	void SelectViewedApplication(EPhoneApplication PhoneApplication);
protected:
	UPROPERTY()
	AMobilePhone* MobilePhone;

	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	UMainCharacterAnimInstance* AnimInstance;
	
	/*  ---  Input Actions  ---  */

	UPROPERTY()
	UInputAction* TakePhoneInOrOutOfHandsAction;
	
	/*  ---  Functions  ---  */
	
	UFUNCTION()
	void ChoosePhoneTakeOrPut();

	UFUNCTION()
	void TakePhoneInHands();
	
	UFUNCTION()
	void PutPhoneInPocket();
	
	UFUNCTION()
	void ChangePhoneFocusState();

	/*  --- Variables  ---  */
	
	bool bIsPhoneFocused = false;
	bool bCanChangePhoneSituation = true;

	EPhoneSituation PhoneSituation;
	
	FTimerHandle ChangePhoneSituationTimerHandle;
	
private:
	const FVector MOBILE_PHONE_OUT_OF_BOUNDS_LOCATION = FVector(0,0,-30);
};
