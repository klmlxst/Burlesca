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
	ShowCursor();
	
	SetPause(true);
}

void ABurlescaPlayerController::UnpauseGame()
{
	SignalBus->GetGlobalGameEventsContainer()->OnGameUnpaused.Broadcast();
	bIsGamePaused = false;

	HideCursor();
	SetPause(false);
}

void ABurlescaPlayerController::ShowCursor()
{
	bShowMouseCursor = true;
}

void ABurlescaPlayerController::HideCursor()
{
	bShowMouseCursor = false;
}
