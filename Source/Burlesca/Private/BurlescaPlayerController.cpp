// Fill out your copyright notice in the Description page of Project Settings.


#include "BurlescaPlayerController.h"

#include "Framework/SignalBus.h"

void ABurlescaPlayerController::Init(USignalBus* signalBus)
{
	SignalBus = signalBus;
}

void ABurlescaPlayerController::PauseGame()
{
	SignalBus->GetGlobalGameEventsContainer()->OnGamePaused.Broadcast();
	bIsGamePaused = true;
	bShowMouseCursor = true;
	
	SetPause(true);
}

void ABurlescaPlayerController::UnpauseGame()
{
	SignalBus->GetGlobalGameEventsContainer()->OnGameUnpaused.Broadcast();
	bIsGamePaused = false;
	bShowMouseCursor = false;
	
	SetPause(false);
}
