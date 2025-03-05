// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/ApplicationWidgets/Chat/Components/DialogueCompanionButton.h"

void UDialogueCompanionButton::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UDialogueCompanionButton::UDialogueCompanionButton::OnButtonClicked);
}
