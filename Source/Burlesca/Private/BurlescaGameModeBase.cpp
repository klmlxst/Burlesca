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
	
	for(TObjectIterator<UObject> obj; obj; ++obj )
	{
		if (obj->GetWorld() == GetWorld())
		{
			if(obj->Implements<UInject>())
			{
				Cast<IInject>(*obj)->Inject(DiContainer);
			}
		
			if(obj->Implements<UInputSetupable>())
			{
				Cast<IInputSetupable>(*obj)->SetupInput(EnhancedInputComponent);
			}
		}
	}
}
