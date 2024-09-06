// Copyright Uncertain Studios (c). All Rights Reserved.


#include "BurlescaGameModeBase.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "InputSetupable.h"
#include "Framework/DependencyInjection/Inject.h"
#include "Framework/DependencyInjection/SceneContext.h"

ABurlescaGameModeBase::ABurlescaGameModeBase()
{
	DefaultPawnClass = nullptr;
}

void ABurlescaGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	ASceneContext* SceneContext = nullptr;
	
	for(TActorIterator<ASceneContext> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		SceneContext = *Iterator;
	}

	if(SceneContext)
	{
		SceneContext->InitDiContainer();
	}	

	SceneContext->StartInstallers();
	
	UDependencyContainer* DiContainer = SceneContext->GetDIContainer();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(DiContainer->Resolve<APlayerController>()->InputComponent);
	
	for(TActorIterator<AActor> It(GetWorld()); It; ++It )
	{
		if(It->Implements<UInject>())
		{
			Cast<IInject>(*It)->Inject(DiContainer);
		}
		
		if(It->Implements<UInputSetupable>())
		{
			Cast<IInputSetupable>(*It)->SetupInput(EnhancedInputComponent);
		}
	}
}
