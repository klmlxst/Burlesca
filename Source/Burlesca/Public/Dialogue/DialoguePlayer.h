// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphAsset.h"
#include "DialogueGraphRuntimeGraph.h"
#include "UObject/Object.h"
#include "DialoguePlayer.generated.h"

UCLASS()
class BURLESCA_API UDialoguePlayer : public UObject
{
	GENERATED_BODY()

public:
	UDialoguePlayer() {  }
	void Init();
	
	void ProvideDialoguesAssets(TArray<UDialogueGraphAsset*> dialogues) //1st - friend ; 
	{
		friendDialogue = dialogues[0];
	}

	

protected:
	UPROPERTY()
	UDialogueGraphAsset* friendDialogue;
};
