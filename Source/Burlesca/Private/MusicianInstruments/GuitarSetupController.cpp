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
}


void UGuitarSetupController::InitInputActions(UInputAction* switchPegAction, UInputAction* rotatePegAction, UInputAction* playStringAction)
{
	SwitchPegAction = switchPegAction;
	RotatePegAction = rotatePegAction;
	PlayStringAction = playStringAction;
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
		if (!Peg->IsTuned())
		{
			Peg->Deselect();
		}
	}
}


void UGuitarSetupController::StartGuitarSetup()
{
	bIsGuitarSetsUp = true;
	MainCharacter->MoveCameraTo(GuitarSetupViewPlaceholder, 0.5f, true);
	GetWorld()->GetTimerManager().SetTimer(GuitarSetupDelay,this, &UGuitarSetupController::OnDelayTimerEnds,
		0.5f, false);
}

bool UGuitarSetupController::GetIsGuitarSetsUp() const
{
	return bIsGuitarSetsUp;
}

float UGuitarSetupController::CalculatePitchFromRotation(float RotationValue) const
{
	float MinRotation = 0.0f;
	float MaxRotation = 10.0f;
	
	float MinPitchMultiplier = 0.5f;
	float MaxPitchMultiplier = 2.0f;
	
	float NormalizedRotation = FMath::Clamp((RotationValue - MinRotation) / (MaxRotation - MinRotation), 0.0f, 1.0f);
	
	float PitchMultiplier = FMath::Lerp(MinPitchMultiplier, MaxPitchMultiplier, NormalizedRotation);

	return PitchMultiplier;
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
	if (bIsTimerSucceed && !bIsBlocked && TuningPegs.Num() > 0)
	{
		if (TuningPegs.Num() < 6)
		{
			UE_LOG(LogTemp, Error, TEXT("Not enough tuning pegs"));
			return;
		}

		int32 PreviousSelectedPeg = CurrentSelectedTuningPeg;
		do
		{
			if (Value.Get<float>() < 0)
			{
				if (CurrentSelectedTuningPeg > 0)
				{
					CurrentSelectedTuningPeg--;
				}
				else
				{
					CurrentSelectedTuningPeg = TuningPegs.Num() - 1;
				}
			}
			else if (Value.Get<float>() > 0)
			{
				if (CurrentSelectedTuningPeg < TuningPegs.Num() - 1)
				{
					CurrentSelectedTuningPeg++;
				}
				else
				{
					CurrentSelectedTuningPeg = 0;
				}
			}
		} while (CurrentSelectedTuningPeg != PreviousSelectedPeg && TuningPegs[CurrentSelectedTuningPeg]->IsTuned());

		if (CurrentSelectedTuningPeg != PreviousSelectedPeg)
		{
			TuningPegs[PreviousSelectedPeg]->Deselect();
			TuningPegs[CurrentSelectedTuningPeg]->Select();
		}
	}
}


void UGuitarSetupController::RotatePeg(const FInputActionValue& Value)
{
	ATuningPegs* SelectedPeg = TuningPegs[CurrentSelectedTuningPeg];
    if (bIsGuitarSetsUp && !bIsBlocked && TuningPegs.Num() > 0)
    {
            float DirectionValue = Value.Get<float>();

            if (FMath::IsNearlyZero(DirectionValue, 0))
            {
                ERotationDirection RotationDirection = DirectionValue > 0 ? ERotationDirection::Right : ERotationDirection::Left;
                SelectedPeg->Rotate(RotationDirection);

                if (SelectedPeg->IsInCorrectPosition() && SelectedPeg->IsTuned())
                {
                    SelectedPeg->SetComplete();
                    UE_LOG(LogTemp, Log, TEXT("Peg is in the correct position"));
                	
                    GetWorld()->GetTimerManager().SetTimer(BlockActionsHandle, this, &UGuitarSetupController::UnblockActions, 0.5f, false);
                    bIsBlocked = true;
                	SelectedPeg->SetTuned(true);
                	
                    GetWorld()->GetTimerManager().SetTimer(GuitarSetupDelay, this, &UGuitarSetupController::SwitchToNextPeg, 0.5f, false);
                }
                else
                {
                    UE_LOG(LogTemp, Log, TEXT("Peg is not in the correct position"));
                }
            }
        }
}

void UGuitarSetupController::SwitchToNextPeg()
{
    if (CurrentSelectedTuningPeg < TuningPegs.Num() - 1)
    {
        TuningPegs[CurrentSelectedTuningPeg]->Deselect();
        CurrentSelectedTuningPeg++;
        TuningPegs[CurrentSelectedTuningPeg]->Select();
        UE_LOG(LogTemp, Log, TEXT("Switched to next peg: %d"), CurrentSelectedTuningPeg);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("All pegs are tuned. Guitar setup is complete."));
        StopGuitarSetup();
    }
}

void UGuitarSetupController::UnblockActions()
{
    bIsBlocked = false;
    UE_LOG(LogTemp, Log, TEXT("Actions are unblocked"));
}


void UGuitarSetupController::PlayGuitarString(const FInputActionValue& Value)
{
	if (bIsGuitarSetsUp && TuningPegs.Num() > 0)
	{
		if (ATuningPegs* SelectedPeg = TuningPegs[CurrentSelectedTuningPeg])
		{
			if (SelectedPeg->IsInCorrectPosition() && SelectedPeg->IsTuned())
			{
				if (AudioComponent && SuccessSound && SelectedPeg->IsTuned())
				{
					AudioComponent->SetSound(SuccessSound);
					AudioComponent->SetPitchMultiplier(1.0f);
					AudioComponent->Play();
				}
				UE_LOG(LogTemp, Log, TEXT("String is tuned! Playing success sound."));
			}
			else
			{
				
				float CurrentPitch = CalculatePitchFromRotation(SelectedPeg->GetCurrentRotation());

				if (AudioComponent && StringSound)
				{
					AudioComponent->SetSound(StringSound);
					AudioComponent->SetPitchMultiplier(CurrentPitch);
					AudioComponent->Play();
				}
				UE_LOG(LogTemp, Log, TEXT("String is not tuned. Playing sound with pitch: %f"), CurrentPitch);
			}
		}
	}
}



