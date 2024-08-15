// Copyright Uncertain Studios (c). All Rights Reserved.


#include "BurlescaGameModeBase.h"

#include "Framework/DependencyInjection/DependencyInjection.h"

ABurlescaGameModeBase::ABurlescaGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_MainCharacter")); 
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Searched character blueprints is null ptr"));
	}

	UE_LOG(DependencyInjection, Warning, TEXT("GameModeConstruction"));
}
