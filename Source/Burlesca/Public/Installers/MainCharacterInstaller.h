// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/DependencyInjection/InjectionInstaller.h"
#include "MainCharacterInstaller.generated.h"

class UMainCharacterAnimInstance;
class AMainCharacter;

UCLASS()
class BURLESCA_API AMainCharacterInstaller : public AInjectionInstaller
{
	GENERATED_BODY()

public:
	AMainCharacterInstaller();
	virtual void InstallBindings(UDependencyContainer* Container) override;
	virtual void Start(UDependencyContainer* Container) override;
protected:
	UPROPERTY()
	AMainCharacter* MainCharacter;

	UPROPERTY()
	UMainCharacterAnimInstance* MainCharacterAnimInstance;

	UPROPERTY(EditAnywhere, Category = "Character Settings|Animation")
	TSubclassOf<UAnimInstance> AnimInstanceClass;
	
	UPROPERTY(EditAnywhere, Category = "Character Settings")
	TSubclassOf<ACharacter> CharacterClass;

	UPROPERTY(EditAnywhere, Category = "Character Settings")
	FVector CharacterSpawnPosition;

	UPROPERTY(EditAnywhere, Category = "Character Settings")
	FRotator CharacterSpawnRotation;
};
