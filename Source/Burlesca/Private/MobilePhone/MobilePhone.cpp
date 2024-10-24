// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/MobilePhone.h"

#include "Components/WidgetComponent.h"
#include "MobilePhone/MobilePhoneEnums.h"
#include "MobilePhone/ApplicationWidgets/Chat/ChatScreen.h"
#include "MobilePhone/ApplicationWidgets/Flashlight/FlashlightScreen.h"
#include "MobilePhone/ApplicationWidgets/GuitarTuner/GuitarTunerScreen.h"
#include "MobilePhone/ApplicationWidgets/Home/HomeScreen.h"

AMobilePhone::AMobilePhone()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMesh);
	
	MobilePhoneScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Mobile Screen Widget"));
	MobilePhoneScreenWidgetComponent->SetupAttachment(RootComponent);
	MobilePhoneScreenWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
}

void AMobilePhone::SetupInput(UEnhancedInputComponent* Input)
{
	WidgetsCreation();

	HomeScreenWidget->SetupInput(Input);
	FlashlightWidget->SetupInput(Input);
	ChatScreenWidget->SetupInput(Input);
	GuitarTunerScreenWidget->SetupInput(Input);
}

void AMobilePhone::SetPowerState(bool bPowerOn)
{
	switch (bPowerOn)
	{
	case true:
		OpenedPhoneApplication = EPhoneApplication::HomePage;
		HomeScreenWidget->OpenApplication();
		break;

	case false:
		HomeScreenWidget->DeactivateApplication();
		HomeScreenWidget->CloseApplication();
		ChatScreenWidget->DeactivateApplication();
		ChatScreenWidget->CloseApplication();
		break;
	}
}

void AMobilePhone::SetVisibility(bool bIsVisible) const
{
	StaticMesh->SetVisibility(bIsVisible);
	MobilePhoneScreenWidgetComponent->SetVisibility(bIsVisible);
}

void AMobilePhone::OnPhoneFocused()
{
	switch(OpenedPhoneApplication)
	{
	case EPhoneApplication::HomePage:
		HomeScreenWidget->ActivateApplication();
		break;
	case EPhoneApplication::Chat:
		ChatScreenWidget->ActivateApplication();
		break;
	}
}

void AMobilePhone::OnPhoneUnfocused()
{
	switch(OpenedPhoneApplication)
	{
	case EPhoneApplication::HomePage:
		HomeScreenWidget->DeactivateApplication();
		break;
	case EPhoneApplication::Chat:
		ChatScreenWidget->DeactivateApplication();
		break;
	}
}

void AMobilePhone::WidgetsCreation()
{
	Super::BeginPlay();

	check(MobilePhoneScreenWidgetComponent);

	check(HomeScreenWidgetClass);
	check(ChatScreenWidgetClass);
	check(FlashlightWidgetClass);
	check(GuitarTunerWidgetClass);
	
	HomeScreenWidget = CreateWidget<UHomeScreen>(GetWorld(), HomeScreenWidgetClass);
	ChatScreenWidget = CreateWidget<UChatScreen>(GetWorld(), ChatScreenWidgetClass);
	FlashlightWidget = CreateWidget<UFlashlightScreen>(GetWorld(), FlashlightWidgetClass);
	GuitarTunerScreenWidget = CreateWidget<UGuitarTunerScreen>(GetWorld(), GuitarTunerWidgetClass);
	
	HomeScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	ChatScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	FlashlightWidget->SetVisibility(ESlateVisibility::Collapsed);
	GuitarTunerScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	if (HomeScreenWidget)
	{
		MobilePhoneScreenWidgetComponent->SetWidget(HomeScreenWidget);
	}

	HomeScreenWidget->OnApplicationOpenCalled.AddDynamic(this, &AMobilePhone::OpenApplication);
}

void AMobilePhone::OpenApplication(EPhoneApplication application)
{
	HomeScreenWidget->DeactivateApplication();
	HomeScreenWidget->CloseApplication();

	switch(application)
	{
		case EPhoneApplication::Chat:
			ChatScreenWidget->OpenApplication();
			ChatScreenWidget->ActivateApplication();
			MobilePhoneScreenWidgetComponent->SetWidget(ChatScreenWidget);
			break;

		case EPhoneApplication::Flashlight:
			FlashlightWidget->OpenApplication();
			FlashlightWidget->ActivateApplication();
			MobilePhoneScreenWidgetComponent->SetWidget(FlashlightWidget);
			break;

		case EPhoneApplication::GuitarSetup:
			GuitarTunerScreenWidget->OpenApplication();
			GuitarTunerScreenWidget->ActivateApplication();
			MobilePhoneScreenWidgetComponent->SetWidget(GuitarTunerScreenWidget);
			break;
	}
}



