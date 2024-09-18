// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/MobilePhone.h"

#include "Components/WidgetComponent.h"
#include "MobilePhone/MobilePhoneEnums.h"
#include "MobilePhone/ApplicationWidgets/Chat/ChatScreen.h"
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

	check(HomeScreenWidgetClass);
	check(MobilePhoneScreenWidgetComponent);
	
	HomeScreenWidget = CreateWidget<UHomeScreen>(GetWorld(), HomeScreenWidgetClass);
	HomeScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	if (HomeScreenWidget)
	{
		MobilePhoneScreenWidgetComponent->SetWidget(HomeScreenWidget);
	}
}



