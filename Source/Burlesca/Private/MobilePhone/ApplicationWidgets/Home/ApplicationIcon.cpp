// Fill out your copyright notice in the Description page of Project Settings.


#include "MobilePhone/ApplicationWidgets/Home/Components/ApplicationIcon.h"
#include "Components/Image.h"

void UApplicationIcon::Select()
{
	if (SelectBorder)
	{
		SelectBorder->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SelectBorder is null!"));
	}
}

void UApplicationIcon::Deselect()
{
	SelectBorder->SetVisibility(ESlateVisibility::Collapsed);
}

void UApplicationIcon::NativeConstruct()
{
	Deselect();
}
