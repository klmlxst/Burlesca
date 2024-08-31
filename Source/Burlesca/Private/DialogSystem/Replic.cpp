// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogSystem/Replic.h"

float UReplic::GetDisplayReplic() const
{
	return DisplayTime;
}

FText UReplic::GetReplic() const
{
	return ReplicText;
}

void UReplic::SetReplic(FText Replic, float DelataReplic)
{
	ReplicText = Replic;
	DisplayTime = DelataReplic;
}

