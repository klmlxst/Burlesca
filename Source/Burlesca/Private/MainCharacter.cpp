// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacter.h"

#include "BurlescaPlayerController.h"
#include "MainCharacterAnimInstance.h"
#include "MovieSceneTracksComponentTypes.h"
#include "MainCharacterComponents/TP_MainCharacterCameraController.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MainCharacterComponents/Interaction//TP_MainCharInteractionController.h"
#include "Framework/SignalBus.h"
#include "MainCharacterComponents/TP_MainCharMovementComponent.h"
#include "MobilePhone/MobilePhone.h"
#include "Settings/SettingsContainer.h"

AMainCharacter::AMainCharacter()
{
	ComponentsInitialization();
}

void AMainCharacter::ComponentsInitialization()
{
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	MainCamera->SetupAttachment(RootComponent);
	MainCamera->bUsePawnControlRotation = true;

	ArmsMesh = FindComponentByClass<USkeletalMeshComponent>();
	check(ArmsMesh);
	ArmsMesh->bCastDynamicShadow = false;
	ArmsMesh->CastShadow = false;
	
	CameraController = CreateDefaultSubobject<UTP_MainCharacterCameraController>(TEXT("Camera Movement Controller"));
	MovementController = CreateDefaultSubobject<UTP_MainCharMovementComponent>(TEXT("Player Movement Controller"));
	InteractionController = CreateDefaultSubobject<UTP_MainCharInteractionController>(TEXT("Interaction Controller"));
	check(CameraController);
	check(MovementController);
	check(InteractionController);
}

void AMainCharacter::SetupInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	check(CameraController);
	CameraController->SetupInput(EnhancedInputComponent);
	check(MovementController);
	MovementController->SetupInput(EnhancedInputComponent);
	check(InteractionController)
	InteractionController->SetupInput(EnhancedInputComponent);
}

void AMainCharacter::Inject(UDependencyContainer* Container)
{
	HUD = Container->Resolve<AGameplayHUD>();
	check(HUD);

	SignalBus = Container->Resolve<USignalBus>();
	check(SignalBus);

	UInputSettingsContainer* InputSettingsContainer = Container->Resolve<USettingsContainer>()->GetInputSettingsContainer();
	
	CameraController->Init(MainCamera, SignalBus, InputSettingsContainer);
	InteractionController->Init(MainCamera, HUD, SignalBus);
	
	ABurlescaPlayerController* PlayerController = Container->Resolve<ABurlescaPlayerController>();
	PlayerController->SetViewTarget(this);
	MainCamera->Activate();

	MobilePhone = Container->Resolve<AMobilePhone>();
	AttachPhoneToSocket();
	SubscribeEvents();
}

void AMainCharacter::SubscribeEvents()
{
	check(SignalBus);
	
	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraMovedOutFromCharacter.AddDynamic(this, &AMainCharacter::StopAllPlayerServicies);
	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraReturnedToCharacter.AddDynamic(this, &AMainCharacter::PlayAllPlayerServicies);

	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraMovedOutFromCharacter.AddDynamic(this, &AMainCharacter::DeactivateStaticMesh);
	SignalBus->GetCharacterEventsContainer()->OnCharacterCameraReturnedToCharacter.AddDynamic(this, &AMainCharacter::ActivateStaticMesh);
}

void AMainCharacter::StopAllPlayerServicies()
{
	CameraController->StopService();
	InteractionController->StopService();
	MovementController->StopService();
}

void AMainCharacter::PlayAllPlayerServicies()
{
	CameraController->PlayService();
	InteractionController->PlayService();
	MovementController->PlayService();
}

UMainCharacterAnimInstance* AMainCharacter::CreateAnimInstance(UClass* AnimInstanceClass)
{
	ArmsMesh->SetAnimClass(AnimInstanceClass);
	return Cast<UMainCharacterAnimInstance>(ArmsMesh->GetAnimInstance());
}

void AMainCharacter::MoveCameraTo(AActor* PositionActor, float MovementDuration, bool bIsMovingFromCharacter, bool bIsMovingToCharacter) const
{
	if(CameraController)
	{
		CameraController->MoveCameraTo(PositionActor, MovementDuration, bIsMovingFromCharacter);
	}
}

void AMainCharacter::MoveCameraTo(FVector PositionVector, FRotator RotationVector, float MovementDuration, bool bIsMovingFromCharacter, bool bIsMovingToCharacter) const
{
	if(CameraController)
	{
		CameraController->MoveCameraTo(PositionVector, RotationVector, MovementDuration, bIsMovingFromCharacter);
	}
}

void AMainCharacter::ReturnCameraToCharacter(float MovementDuration) const
{
	if(CameraController)
	{
		CameraController->ReturnCameraToCharacter(MovementDuration);
	}
}

void AMainCharacter::AttachPhoneToSocket()
{
	MobilePhone->AttachToComponent(ArmsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "phone_socket");
}

void AMainCharacter::DetachPhoneFromSocket()
{
	MobilePhone->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}
