// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/MobilePhone.h"

#include "Components/WidgetComponent.h"
#include "HUD/MobilePhoneScreen.h"
#include "MobilePhone/MobilePhoneController.h"

AMobilePhone::AMobilePhone()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMesh);
	
	MobilePhoneScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Mobile Screen Widget"));
	MobilePhoneScreenWidgetComponent->SetupAttachment(RootComponent);
	MobilePhoneScreenWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
}

void AMobilePhone::SetPowerState(bool bPowerOn)
{
	switch (bPowerOn)
	{
	case true:
		MobilePhoneScreenWidget->SetVisibility(ESlateVisibility::Visible);
		break;

	case false:
		MobilePhoneScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	}
}

void AMobilePhone::BeginPlay()
{
	Super::BeginPlay();

	check(MobilePhoneScreenClass);
	check(MobilePhoneScreenWidgetComponent);
	
	MobilePhoneScreenWidget = CreateWidget<UMobilePhoneScreen>(GetWorld(), MobilePhoneScreenClass);
	MobilePhoneScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	if (MobilePhoneScreenWidget)
	{
		MobilePhoneScreenWidgetComponent->SetWidget(MobilePhoneScreenWidget);
	}
}



