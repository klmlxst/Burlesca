// Copyright Uncertain Studios (c). All Rights Reserved.

#include "Framework/DependencyInjection/SceneContext.h"
#include "Framework/DependencyInjection/DependencyInjection.h"


ASceneContext::ASceneContext(): DIContainer(nullptr)
{
	
}

void ASceneContext::InitDiContainer()
{	
	for (AInjectionInstaller* Installer : SceneInstallers)
	{
		Installer->InstallBindings(DIContainer);
	}
}

UDependencyContainer* ASceneContext::GetDIContainer() const
{
	return DIContainer;
}

void ASceneContext::PostInitProperties()
{
	Super::PostInitProperties();

	InitDiContainer();
}

//void ASceneContext::PostLoad()
//{
//	Super::PostLoad();

	
	
	/*if(GetWorld() && GetWorld()->IsGameWorld())
	{
		UE_LOG(DependencyInjection,Warning, TEXT("PostLoadGame"));
		
		InitDiContainer();

		for(TObjectIterator<UObject> Iterator; Iterator; ++Iterator)
		{
			UObject* Object = *Iterator;
			UClass* Class = Object->GetClass();

			for(TFieldIterator<UFunction> j(Class,EFieldIterationFlags::IncludeSuper); j; ++j)
			{
				UFunction* Function = *j;
				if(Function->HasMetaData(TEXT("Inject")))
				{
					void* Parameters = FMemory_Alloca(Function->ParmsSize());
					FMemory::Memzero(Parameters, Function->ParmsSize());

					for(TFieldIterator<FProperty> Property(Function); Property; ++Property)
					{
						FProperty* Param = *Property;

						UClass* ParamClass = Param->
						UObject* ResolvedInstance = DIContainer->Resolve<Class>();
					}
					
					
					Object->ProcessEvent(Function,);
				}
			}
		}	
	}*/
//}
