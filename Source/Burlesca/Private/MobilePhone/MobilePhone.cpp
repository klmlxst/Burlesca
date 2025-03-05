// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/MobilePhone.h"

#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "MobilePhone/MobilePhoneEnums.h"
#include "MobilePhone/ApplicationWidgets/PhoneApplicationContainer.h"
#include "MobilePhone/ApplicationWidgets/Chat/ChatScreen.h"

AMobilePhone::AMobilePhone()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->CastShadow = false;
	SetRootComponent(StaticMesh);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioSource");
	AudioComponent->SetupAttachment(RootComponent);
	
	MobilePhoneScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Mobile Screen Widget"));
	MobilePhoneScreenWidgetComponent->SetupAttachment(RootComponent);
	MobilePhoneScreenWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
}

void AMobilePhone::Init()
{
	AudioComponent->SetSound(NotificationSound);
	ApplicationsContainer = Cast<UPhoneApplicationContainer>(CreateWidget(GetWorld(), ApplicationsContainerClass));
	MobilePhoneScreenWidgetComponent->SetWidget(ApplicationsContainer);
	ApplicationsContainer->SetContainerVisibility(ESlateVisibility::Collapsed);
}

void AMobilePhone::SetPowerState(bool bPowerOn) const
{
	ESlateVisibility visibility = bPowerOn ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	ApplicationsContainer->SetContainerVisibility(visibility);
}

void AMobilePhone::SetVisibility(bool bIsVisible) const
{
	StaticMesh->SetVisibility(bIsVisible);
	MobilePhoneScreenWidgetComponent->SetVisibility(bIsVisible);
}

void AMobilePhone::OnPhoneFocused()
{
	ApplicationsContainer->ActivateCurrentApplication();
}

void AMobilePhone::OnPhoneUnfocused()
{
	ApplicationsContainer->DeactivateCurrentApplication();
}

UPhoneApplication* AMobilePhone::GetApp(EPhoneApplication app)
{
	return ApplicationsContainer->GetApplicationWidget(app);
}
