// Fill out your copyright notice in the Description page of Project Settings.



#include "MusicianInstruments/GuitarSetupController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "MainCharacter.h"
#include "Engine/PointLight.h"
#include "Kismet/GameplayStatics.h"
#include "MusicianInstruments/TuningPegs.h"
#include "Components/AudioComponent.h"


void UGuitarSetupController::Init(AMainCharacter* mainCharacter, USignalBus* signalBus)
{
	MainCharacter = mainCharacter;
	SignalBus = signalBus;
}

void UGuitarSetupController::InitGuitarSetup(AActor* guitarSetupViewPlaceholder, APointLight* leftLight,
	APointLight* rightLight, TArray<ATuningPegs*> tuningPegs)
{
	GuitarSetupViewPlaceholder = guitarSetupViewPlaceholder;
	LeftLight = leftLight;
	RightLight = rightLight;
	TuningPegs = tuningPegs;

	if(TuningPegs.Num() < 6)
	{
		UE_LOG(LogTemp, Error, TEXT("Not enough pegs to apropriate work of guitar tuning minigame"));
	}
}

void UGuitarSetupController::InitAudio(UAudioComponent* audioSource, USoundBase* successSound,
	TArray<USoundBase*> stringSounds)
{
	AudioSource = audioSource;
	SuccessSound = successSound;
	StringSound = stringSounds;
}


void UGuitarSetupController::InitInputActions(UInputAction* switchPegAction, UInputAction* rotatePegAction, UInputAction* playStringAction)
{
	SwitchPegAction = switchPegAction;
	RotatePegAction = rotatePegAction;
	PlayStringAction = playStringAction;
}

void UGuitarSetupController::StartGuitarSetup()
{
	bIsGuitarSetsUp = true;
	MainCharacter->MoveCameraTo(GuitarSetupViewPlaceholder, 0.5f, true);
	GetWorld()->GetTimerManager().SetTimer(GuitarSetupDelay,this, &UGuitarSetupController::OnDelayTimerEnds,
		0.5f, false);
}

void UGuitarSetupController::StopGuitarSetup()
{
	GetWorld()->GetTimerManager().ClearTimer(GuitarSetupDelay);
	MainCharacter->ReturnCameraToCharacter(0.5f);
	ChangeLightActivityState(false);
	bIsGuitarSetsUp = false;
	bIsTimerSucceed = false;

	for(ATuningPegs* Peg : TuningPegs)
	{
		Peg->Deselect();
	}
}

float UGuitarSetupController::CalculatePitchFromRotation(float RotationValue) const
{
	return FMath::Lerp(0.5f, 1.5f, RotationValue / 10);
}


void UGuitarSetupController::ChangeLightActivityState(bool bActivitySate) const
{
	if(LeftLight)
	{
		LeftLight->SetEnabled(bActivitySate);
	}

	if(RightLight)
	{
		RightLight->SetEnabled(bActivitySate);
	}
}

void UGuitarSetupController::OnDelayTimerEnds()
{
	bIsTimerSucceed = true;
	GetWorld()->GetTimerManager().ClearTimer(GuitarSetupDelay);
	ChangeLightActivityState(true);

	TuningPegs[CurrentSelectedTuningPeg]->Select();
}

void UGuitarSetupController::SetupInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(SwitchPegAction, ETriggerEvent::Started,this, &UGuitarSetupController::SwitchPeg);
	EnhancedInputComponent->BindAction(RotatePegAction, ETriggerEvent::Triggered,this, &UGuitarSetupController::RotatePeg);
	EnhancedInputComponent->BindAction(PlayStringAction, ETriggerEvent::Started, this, &UGuitarSetupController::PlayGuitarString);
}

void UGuitarSetupController::SwitchPeg(const FInputActionValue& Value)
{
	if (bIsTimerSucceed)
	{
		TuningPegs[CurrentSelectedTuningPeg]->Deselect();
		
		if (Value.Get<float>() < 0)
		{
			if (CurrentSelectedTuningPeg != 0)
			{
				for(int i = CurrentSelectedTuningPeg - 1; i >= 0; i--)
				{
					if(!TuningPegs[i]->GetIsTuned())
					{
						CurrentSelectedTuningPeg = i;
						break;
					}
				}
			}
		}
		
		else if (Value.Get<float>() > 0)
		{
			if (CurrentSelectedTuningPeg != 5)
			{
				for(int i = CurrentSelectedTuningPeg + 1; i <= 5; i++)
				{
					if(!TuningPegs[i]->GetIsTuned())
					{
						CurrentSelectedTuningPeg = i;
						break;
					}
				}
			}
		}

		TuningPegs[CurrentSelectedTuningPeg]->Select();
	}
}


void UGuitarSetupController::RotatePeg(const FInputActionValue& Value)
{	
    if (bIsGuitarSetsUp)
    {
    	if(Value.Get<float>() != 0)
    	{
    		ERotationDirection RotationDirection = Value.Get<float>() > 0 ? ERotationDirection::Right : ERotationDirection::Left;

    		TuningPegs[CurrentSelectedTuningPeg]->Rotate(RotationDirection);
    	}

    	if(TuningPegs[CurrentSelectedTuningPeg]->GetIsTuned())
    	{
    		uint8 tunnedQuantity = 0;
    		for(ATuningPegs* Peg : TuningPegs)
    		{
    			if(Peg->GetIsTuned())
    			{
    				tunnedQuantity++;
    			}
    		}
    		if(tunnedQuantity == 6)
    		{
    			bIsGuitarSetupCompleted = true;
    			OnGuitarSetupComplete.Broadcast();
    			StopGuitarSetup();
    		}

    		for(int i = CurrentSelectedTuningPeg + 1; i <= 5; i++)
    		{
    			if(!TuningPegs[i]->GetIsTuned())
    			{
    				CurrentSelectedTuningPeg = i;
    				TuningPegs[CurrentSelectedTuningPeg]->Select();
					return;
    			}
    		}

    		for(int i = CurrentSelectedTuningPeg - 1; i >= 0; i--)
    		{
    			if(!TuningPegs[i]->GetIsTuned())
    			{
    				CurrentSelectedTuningPeg = i;
    				TuningPegs[CurrentSelectedTuningPeg]->Select();
    				return;
    			}
    		}
    	}
    }
}

void UGuitarSetupController::PlayGuitarString(const FInputActionValue& Value)
{
	if(bIsGuitarSetsUp)
	{
		if(bIsGuitarPlayStringReloaded)
		{
			AudioSource->SetSound(StringSound[CurrentSelectedTuningPeg]);
			AudioSource->SetPitchMultiplier(CalculatePitchFromRotation(TuningPegs[CurrentSelectedTuningPeg]->GetCurrentRotation()));
			AudioSource->Play();
			bIsGuitarPlayStringReloaded = false;
			GetWorld()->GetTimerManager().SetTimer(StringPlayReload, this, &UGuitarSetupController::OnGuitarPlayStringReloaded, 0.5f, false);
		}
	}
}



