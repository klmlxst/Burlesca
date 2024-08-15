// Copyright Uncertain Studios (c). All Rights Reserved.


#include "MainCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "MainCharacterComponents/TP_MainCharacterCameraController.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Framework/DependencyInjection/DependencyInjection.h"
#include "MainCharacterComponents/Interaction//TP_MainCharInteractionController.h"
#include "MainCharacterComponents/TP_MainCharMovementComponent.h"

AMainCharacter::AMainCharacter()
{
	ComponentsInitialization();

	UE_LOG(DependencyInjection, Log, TEXT("Character constructed"));
}

void AMainCharacter::BeginPlay() 
{
	Super::BeginPlay();

	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	ControllerComponentsSetup();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(CameraController);
	CameraController->SetupInput(PlayerInputComponent);
	check(MovementController);
	MovementController->SetupInput(PlayerInputComponent);
	check(InteractionController)
	InteractionController->SetupInput(PlayerInputComponent);
}

void AMainCharacter::Construct()
{
	UE_LOG(DependencyInjection, Log, TEXT("Inject nothing"));
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

void AMainCharacter::ControllerComponentsSetup()
{
	CameraController->Init(MainCamera);
	InteractionController->Init(MainCamera);
}

