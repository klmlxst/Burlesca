// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacterComponents/Interaction/TP_MainCharInteractionController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Framework/SignalBus.h"
#include "InteractableObjects/Interactable.h"
#include "MainCharacterComponents/Interaction/InteractionCaseController.h"

UTP_MainCharInteractionController::UTP_MainCharInteractionController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTP_MainCharInteractionController::Init(UCameraComponent* camera, AGameplayHUD* hud, USignalBus* signalBus)
{
	MainCamera = camera;
	check(MainCamera);
	
	check(GetOwner());
	Owner = GetOwner();

	SignalBus = signalBus;
	
	InteractionController = NewObject<UInteractionCaseController>(this);
	InteractionController->Init(hud);

	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraReturnedToCharacter.AddDynamic(this, &UTP_MainCharInteractionController::ResetCurrentInteractable);
}

void UTP_MainCharInteractionController::SetupInput(UEnhancedInputComponent* input)
{
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(input);	
	check(enhancedInputComponent);
	
	enhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &UTP_MainCharInteractionController::PerformInteract);
}

void UTP_MainCharInteractionController::PerformInteract()
{
	if(!bIsServiceStoped)
	{
		InteractionController->InteractionCalled();	
	}
}

void UTP_MainCharInteractionController::ResetCurrentInteractable()
{
	CurrentInteractable = nullptr;
}


void UTP_MainCharInteractionController::PlayService()
{
	bIsServiceStoped = false;
}

void UTP_MainCharInteractionController::StopService()
{
	bIsServiceStoped = true;
}

void UTP_MainCharInteractionController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bIsServiceStoped)
	{
		PerformInteractableCheck();	
	}
}

void UTP_MainCharInteractionController::PerformInteractableCheck()
{
	FHitResult InfoCastHit;
	FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(Owner);

	FVector TraceStart = MainCamera->GetComponentLocation();
	FVector TraceEnd = TraceStart + (MainCamera->GetComponentRotation().Vector() * InfoCastLength );
	
	if (GetWorld()->LineTraceSingleByChannel(InfoCastHit, TraceStart, TraceEnd, ECC_Visibility, CollisionParams))
	{
		AActor* HitActor = InfoCastHit.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			if(HitActor != CurrentInteractable)
			{
				CurrentInteractable = HitActor;
				InteractionController->InteractableFound(HitActor);
				return;
			}

			if(HitActor == CurrentInteractable)
			{
				return;
			}
		}
		else
		{
			InteractionController->InteractableNotFound();
			ResetCurrentInteractable();
		}
	}

	InteractionController->InteractableNotFound();
	ResetCurrentInteractable();
}


/*void UTP_MainCharInteractionController::BeginInteract()
{
	PerformInteractableCheck();

	if(InteractionData.CurrentInteractable)
	{
		if(IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->StartInteraction();

			if(FMath::IsNearlyZero(TargetInteractable->GetInteractableObjectInfo()->InteractionDuration,0.1f))
			{
				Interact();
			}
			else
			{
				Owner->GetWorldTimerManager().SetTimer(TimerHandle_Interaction,this,&UTP_MainCharInteractionController::Interact,
					TargetInteractable->GetInteractableObjectInfo()->InteractionDuration, false);
			}
		}
	}

	UE_LOG(LogTemp,Warning,TEXT("Called begin interact in component"));
}*/

/*void UTP_MainCharInteractionController::EndInteract()
{
	Owner->GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if(IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteraction();	
	}

	UE_LOG(LogTemp,Warning,TEXT("Called end interact in component"));
}*/
