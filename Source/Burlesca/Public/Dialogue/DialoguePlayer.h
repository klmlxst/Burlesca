// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphAsset.h"
#include "DialogueGraphRuntimeGraph.h"
#include "Framework/DependencyInjection/Inject.h"
#include "NodeInfo/DialogueGraphQuoteNodeInfo.h"
#include "NodeInfo/DialogueGraphResponseNodeInfo.h"
#include "UObject/Object.h"
#include "DialoguePlayer.generated.h"

class USignalBus;
enum class EDialogueCompanion;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMessageSend, EDialogueCompanion, companion, UDialogueGraphQuoteNodeInfo*, quote);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestSend, EDialogueCompanion, companion, TArray<UDialogueGraphResponseNodeInfo*>, responses);

UCLASS()
class BURLESCA_API UDialoguePlayer : public UObject, public IInject
{
	GENERATED_BODY()

public:
	//init
	UDialoguePlayer() {  }
	void Init(float betweenMessageDelay);
	virtual void Inject(UDependencyContainer* Container) override;
	
	void ProvideDialoguesAssets(TArray<UDialogueGraphAsset*> dialogues) //1st - friend; 2nd - payer; 3rd - monster;
	{
		friendDialogue = dialogues[0];
		payerDialogue = dialogues[1];
	}
	
	//dialogue

	UDialogueGraphRuntimeNode* GetCurrentNode(EDialogueCompanion companion) { return companionToAssetMap[companion]->Graph->CurrentDialogueNode; }
	void MoveToNextNode(EDialogueCompanion companion) {	companionToAssetMap[companion]->Graph->GoToNextNode(); }
	
	UFUNCTION()
	void StartDialogue(EDialogueCompanion companion);

	UFUNCTION()
	void ResponseChoosed(EDialogueCompanion companion, uint8 responseId  /* starts from 0 */);
	
	FOnMessageSend OnMessageSend;
	FOnRequestSend OnRequestSend;

protected:
	UFUNCTION()
	void PlayDialogue(EDialogueCompanion companion);
	void CallPlayDialogueUsingTimerHandle(EDialogueCompanion companion, float delay);
	
	UPROPERTY()
	UDialogueGraphAsset* friendDialogue = nullptr;

	UPROPERTY()
	UDialogueGraphAsset* payerDialogue = nullptr;
	
	UPROPERTY()
	UDialogueGraphAsset* monsterDialogue = nullptr;

	UPROPERTY()
	TMap<EDialogueCompanion, UDialogueGraphAsset*> companionToAssetMap;
	
	UPROPERTY()
	USignalBus* SignalBus = nullptr;
	
	float DefaultBetweenMessageDelayTime = 1.0f;
	
	FTimerHandle friendMessageDelayTimerHandle;
	FTimerHandle payerMessageDelayTimerHandle;
	FTimerHandle monsterMessageDelayTimerHandle;

	UPROPERTY()
	TMap<EDialogueCompanion, FTimerHandle> companionToTimerHandleMap;
};
