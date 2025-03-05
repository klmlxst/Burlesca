// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/ApplicationWidgets/PhoneApplicationContainer.h"
#include "MobilePhone/ApplicationWidgets/Chat/ChatScreen.h"
#include "MobilePhone/ApplicationWidgets/Home/HomeScreen.h"
#include "MobilePhone/ApplicationWidgets/Flashlight/FlashlightScreen.h"
#include "MobilePhone/ApplicationWidgets/GuitarTuner/GuitarTunerScreen.h"

void UPhoneApplicationContainer::NativeConstruct()
{
	Super::NativeConstruct();

	ApplicationEnumToWidgetMap.Add(EPhoneApplication::HomePage, HomeScreenWidget);
	ApplicationEnumToWidgetMap.Add(EPhoneApplication::Chat, ChatScreenWidget);
	ApplicationEnumToWidgetMap.Add(EPhoneApplication::Flashlight, FlashlightWidget);
	ApplicationEnumToWidgetMap.Add(EPhoneApplication::GuitarSetup, GuitarTunerScreenWidget);

	for(TPair<EPhoneApplication, UPhoneApplication*> app : ApplicationEnumToWidgetMap)
	{
		app.Value->OnApplicationClosed.AddDynamic(this, &UPhoneApplicationContainer::OnApplicationClosed);
		app.Value->SetVisibility(ESlateVisibility::Collapsed);
	}

	HomeScreenWidget->OnApplicationOpenCalled.AddDynamic(this, &UPhoneApplicationContainer::OpenApplication);
	HomeScreenWidget->OpenApplication(); 
}

void UPhoneApplicationContainer::OpenApplication(EPhoneApplication application)
{
	OpenedPhoneApplication = application;
	UPhoneApplication* appWidget = ApplicationEnumToWidgetMap[OpenedPhoneApplication];
	HomeScreenWidget->CloseApplication();
	appWidget->OpenApplication();
	appWidget->ActivateApplication();
}

void UPhoneApplicationContainer::OnApplicationClosed()
{
	OpenedPhoneApplication = EPhoneApplication::HomePage;
	HomeScreenWidget->OpenApplication();
	HomeScreenWidget->ActivateApplication();
}

UPhoneApplication* UPhoneApplicationContainer::GetCurrentOpenedApplication()
{
	return ApplicationEnumToWidgetMap[OpenedPhoneApplication];
}

UPhoneApplication* UPhoneApplicationContainer::GetApplicationWidget(EPhoneApplication app)
{
	return ApplicationEnumToWidgetMap[app];
}

void UPhoneApplicationContainer::ActivateCurrentApplication()
{
	ApplicationEnumToWidgetMap[OpenedPhoneApplication]->ActivateApplication();
}

void UPhoneApplicationContainer::DeactivateCurrentApplication()
{
	ApplicationEnumToWidgetMap[OpenedPhoneApplication]->DeactivateApplication();
}

void UPhoneApplicationContainer::SetContainerVisibility(ESlateVisibility visibility)
{
	SetVisibility(visibility);
}
