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

void AMobilePhone::BeginPlay()
{
	Super::BeginPlay();

	if(MobilePhoneScreenWidgetComponent && MobilePhoneScreenClass)
	{
		MobilePhoneScreenWidget = CreateWidget<UMobilePhoneScreen>(GetWorld(), MobilePhoneScreenClass);

		if(MobilePhoneScreenWidget)
		{
			MobilePhoneScreenWidgetComponent->SetWidget(MobilePhoneScreenWidget);
		}
	}
}



