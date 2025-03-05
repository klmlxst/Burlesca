// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/DialoguePlayer.h"

#include "Dialogue/DialogueCompanion.h"
#include "Dialogue/DialogueSystemManager.h"
#include "Framework/SignalBus.h"

void UDialoguePlayer::Inject(UDependencyContainer* Container)
{
	SignalBus = Container->Resolve<USignalBus>();
}


void UDialoguePlayer::Init(float betweenMessageDelay)
{
	DefaultBetweenMessageDelayTime = betweenMessageDelay;
	
	companionToAssetMap.Add(EDialogueCompanion::Friend, friendDialogue);
	companionToAssetMap.Add(EDialogueCompanion::Payer, payerDialogue);
	companionToAssetMap.Add(EDialogueCompanion::Monster, monsterDialogue);

	companionToTimerHandleMap.Add(EDialogueCompanion::Friend, friendMessageDelayTimerHandle);
	companionToTimerHandleMap.Add(EDialogueCompanion::Payer, payerMessageDelayTimerHandle);
	companionToTimerHandleMap.Add(EDialogueCompanion::Monster, monsterMessageDelayTimerHandle);

	StartDialogue(EDialogueCompanion::Friend);
	StartDialogue(EDialogueCompanion::Payer);
	
	//SignalBus->GetDialogueEventContainer()->OnStartDialogue.AddDynamic(this, &UDialoguePlayer::StartDialogue);
}

void UDialoguePlayer::StartDialogue(EDialogueCompanion companion)
{
	UDialogueGraphAsset* workingDialogueAsset = companionToAssetMap[companion];

	workingDialogueAsset->bIsDialogueActive = true;
	UDialogueGraphRuntimeNode* startNode = workingDialogueAsset->Graph->GetNodeWithId(1);
	workingDialogueAsset->Graph->CurrentDialogueNode = startNode;
	MoveToNextNode(companion);
	float delay = startNode->NodeInfo->GetDelayTime() == -1 ? DefaultBetweenMessageDelayTime : startNode->NodeInfo->GetDelayTime();
	CallPlayDialogueUsingTimerHandle(companion, delay);
}

void UDialoguePlayer::CallPlayDialogueUsingTimerHandle(EDialogueCompanion companion, float delay)
{
	if(delay == 0)
	{
		PlayDialogue(companion);
		return;
	}
	
	GetWorld()->GetTimerManager().SetTimer(
	companionToTimerHandleMap[companion],
	[this, companion] { PlayDialogue(companion); },
	delay,
	false 
	);
}

void UDialoguePlayer::PlayDialogue(EDialogueCompanion companion)
{
	UDialogueGraphRuntimeNode* currentNode = GetCurrentNode(companion);
	if(currentNode == nullptr)
	{
		UE_LOG(DialogueGraphRuntime, Warning, TEXT("UDialoguePlayer::PlayDialogue : No Current Node In Dialogue"));
		return;
	}

	if(currentNode->NodeType == EDialogueGraphNodeType::QuoteNode)
	{
		OnMessageSend.Broadcast(companion, Cast<UDialogueGraphQuoteNodeInfo>(currentNode->NodeInfo));
	}
	if(currentNode->NodeType == EDialogueGraphNodeType::EndNode)
		return;
	if(currentNode->NodeType == EDialogueGraphNodeType::RequestNode)
	{
		TArray<UDialogueGraphResponseNodeInfo*> requestInfo;
		for(UDialogueGraphRuntimeNode* node : currentNode->GetAllNextNodes())
		{
			if(node->NodeInfo != nullptr)
			{
				UDialogueGraphResponseNodeInfo* responseNodeInfo = Cast<UDialogueGraphResponseNodeInfo>(node->NodeInfo);
				if(!responseNodeInfo->bIsAlreadyShown)
					requestInfo.Add(responseNodeInfo);
			}
		}
		OnRequestSend.Broadcast(companion, requestInfo);
		return;
	}
	
	float delay = currentNode->NodeInfo->GetDelayTime() == -1 ? DefaultBetweenMessageDelayTime : currentNode->NodeInfo->GetDelayTime();
	MoveToNextNode(companion);
	CallPlayDialogueUsingTimerHandle(companion, delay);
}

void UDialoguePlayer::ResponseChoosed(EDialogueCompanion companion, uint8 responseId)
{
	UDialogueGraphRuntimeNode* node = companionToAssetMap[companion]->Graph->CurrentDialogueNode->GetNextNode(responseId);

	if(!node)
	{
		UE_LOG(DialogueGraphRuntime, Error, TEXT("Response id is out of range of request node pins!"))
		return;
	}

	Cast<UDialogueGraphResponseNodeInfo>(node->NodeInfo)->bIsAlreadyShown = true;
	companionToAssetMap[companion]->Graph->CurrentDialogueNode = node;
	MoveToNextNode(companion);
	float delay = node->NodeInfo->GetDelayTime() == -1 ? DefaultBetweenMessageDelayTime : node->NodeInfo->GetDelayTime();
	CallPlayDialogueUsingTimerHandle(companion, delay);
}