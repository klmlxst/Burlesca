#pragma once

#include <InputSetupable.h>

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "UObject/Object.h"
#include "GuitarSetupController.generated.h"

struct FInputActionValue;

class UInputAction;
class UEnhancedInputComponent;
class ATuningPegs;
class AMobilePhone;
class AMainCharacter;
class USignalBus;
class APointLight;
class UAudioComponent;

BURLESCA_API DECLARE_LOG_CATEGORY_EXTERN(MusicianInstruments, All, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGuitarSetupComplete);

/**
 * @class UGuitarSetupController
 * @brief This class manages the logic for guitar tuning within the game.
 *
 * The UGuitarSetupController handles the process of tuning the guitar, including selecting and rotating tuning pegs,
 * checking string tuning, and playing sounds. It is integrated with input components and manages visual effects
 * during the tuning process, such as lighting.
 */
UCLASS()
class BURLESCA_API UGuitarSetupController : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(AMainCharacter* mainCharacter, USignalBus* signalBus);
	void InitGuitarSetup(AActor* guitarSetupViewPlaceholder, APointLight* leftLight, APointLight* rightLight, TArray<ATuningPegs*> tuningPegs);
	void InitAudio(UAudioComponent* audioSource, USoundBase* successSound, TArray<USoundBase*> stringSounds);
	void InitInputActions(UInputAction* switchPegAction, UInputAction* rotatePegAction, UInputAction* playStringAction);

	void StopGuitarSetup();
	void StartGuitarSetup();
	void SetupInput(UEnhancedInputComponent* EnhancedInputComponent);

	bool GetIsGuitarSetsUp() const { return bIsGuitarSetsUp; }
	bool GetIsGuitarSetupCompleted() const { return bIsGuitarSetupCompleted; }
	
	FOnGuitarSetupComplete OnGuitarSetupComplete;
	
protected:
	bool bIsGuitarSetsUp = false;
	bool bIsGuitarSetupCompleted = false;
    bool bIsTimerSucceed = false;
	bool bIsGuitarPlayStringReloaded = true;
	
	uint8 CurrentSelectedTuningPeg = 0;
	
	FTimerHandle GuitarSetupDelay;
	FTimerHandle StringPlayReload;

	UPROPERTY()
	USignalBus* SignalBus;

	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	APointLight* LeftLight;

	UPROPERTY()
	APointLight* RightLight;
	
	UPROPERTY(EditInstanceOnly)
	AActor* GuitarSetupViewPlaceholder;

	UPROPERTY()
	TArray<ATuningPegs*> TuningPegs;

	UPROPERTY()
	UInputAction* SwitchPegAction;
	UPROPERTY()
	UInputAction* RotatePegAction;
	UPROPERTY()
	UInputAction* PlayStringAction;

	UPROPERTY()
    UAudioComponent* AudioSource;
	UPROPERTY()
	USoundBase* SuccessSound;
	UPROPERTY()
	TArray<USoundBase*> StringSound;
	
	float CalculatePitchFromRotation(float RotationValue) const;
	
	void ChangeLightActivityState(bool bActivitySate) const;

	UFUNCTION()
	void OnDelayTimerEnds();

	UFUNCTION()
	void OnGuitarPlayStringReloaded() { bIsGuitarPlayStringReloaded = true; }
	
	UFUNCTION()
	void SwitchPeg(const FInputActionValue& Value);
	
	UFUNCTION()
	void RotatePeg(const FInputActionValue& Value);
	
	UFUNCTION()
	void PlayGuitarString(const FInputActionValue& Value);
};
