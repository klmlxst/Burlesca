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

	/**
	 * @brief Initializes the guitar setup controller with the main character and signal bus.
	 * @param mainCharacter Pointer to the main character.
	 * @param signalBus Pointer to the SignalBus object.
	 */
	void Init(AMainCharacter* mainCharacter, USignalBus* signalBus);

	/**
	* @brief Initializes the guitar setup view, lights, and tuning pegs.
	* @param guitarSetupViewPlaceholder Pointer to the actor used as the view placeholder for the guitar setup.
	* @param leftLight Pointer to the left light source.
	* @param rightLight Pointer to the right light source.
	* @param tuningPegs Array of tuning pegs for the guitar.
	*/
	void InitGuitarSetup(AActor* guitarSetupViewPlaceholder, APointLight* leftLight, APointLight* rightLight, TArray<ATuningPegs*> tuningPegs);

	/**
	 * @brief Initializes input actions for guitar setup.
	 * @param switchPegAction Input action for switching between tuning pegs.
	 * @param rotatePegAction Input action for rotating the tuning pegs.
	 * @param playStringAction Input action for playing the guitar string.
	 */
	void InitInputActions(UInputAction* switchPegAction, UInputAction* rotatePegAction, UInputAction* playStringAction);

	/**
	 * @brief Stops the guitar setup process.
	 *
	 * Resets timers, returns the camera to the character, and disables lighting.
	 * It also deselects the currently selected tuning pegs.
	 */
	void StopGuitarSetup();

	/**
	 * @brief Starts the guitar setup process.
	 *
	 * Moves the camera to the guitar setup view, sets timers, and enables lighting.
	 */
	void StartGuitarSetup();

	/**
	 * @brief Checks if the guitar setup process is active.
	 * @return True if the guitar setup is active, false otherwise.
	 */
	bool GetIsGuitarSetsUp() const;

	/**
	 * @brief Sets up input bindings for the guitar setup process.
	 * @param EnhancedInputComponent Pointer to the enhanced input component used for binding actions.
	 */
	void SetupInput(UEnhancedInputComponent* EnhancedInputComponent);

protected:
	// Guitar setup state
	bool bIsGuitarSetsUp = false;
    bool bIsTimerSucceed = false;
    
	uint8 CurrentSelectedTuningPeg = 0;
	
	FTimerHandle GuitarSetupDelay;
	
	FTimerHandle BlockActionsHandle;

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

	//Input actions
	UPROPERTY()
	UInputAction* SwitchPegAction;
	UPROPERTY()
	UInputAction* RotatePegAction;
	UPROPERTY()
	UInputAction* PlayStringAction;

	// Audio-related components 
	UPROPERTY(VisibleAnywhere, Category="Sound")
    UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* StringSound;
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* SuccessSound;

	
	float CalculatePitchFromRotation(float RotationValue) const;
	/**
	 * @brief Toggles the activity state of the lights.
	 * @param bActivitySate The desired activity state of the lights (true to enable, false to disable).
	 */
	void ChangeLightActivityState(bool bActivitySate) const;

	/**
	 * @brief Handles the end of the setup delay timer.
	 *
	 * This function is called when the delay timer ends, enabling player input and activating the first tuning peg.
	 */
	void OnDelayTimerEnds();

	/**
	* @brief Switches to the next tuning peg after the current one is correctly tuned.
	*/
	UFUNCTION()
	void SwitchPeg(const FInputActionValue& Value);

	/**
	* @brief Unblocks player actions after a short delay.
	*/
	UFUNCTION()
	void RotatePeg(const FInputActionValue& Value);

	/**
	 * @brief Plays the sound associated with the currently selected guitar string.
	 * @param Value Input action value used to trigger the sound.
	 */
	UFUNCTION()
	void PlayGuitarString(const FInputActionValue& Value);

	/**
	* @brief Unblocks player actions after a short delay.
	*/
    void UnblockActions();

	/**
	 * @brief Switches to the next tuning peg after the current one is correctly tuned.
	 */
	UFUNCTION()
    void SwitchToNextPeg();
};
