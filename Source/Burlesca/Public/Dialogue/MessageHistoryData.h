// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueMessage.h"
#include "NodeInfo/DialogueGraphResponseNodeInfo.h"
#include "UObject/Object.h"
#include "MessageHistoryData.generated.h"

UCLASS()
class BURLESCA_API UMessageHistoryData : public UObject
{
	GENERATED_BODY()

public:
	TArray<FDialogueMessage> GetMessageHistory() { return MessageHistory; }
	void AddMessageToHistory(FDialogueMessage message) { MessageHistory.Add(message); }
	void AddMessageToHistory(EMessageType messageType, FText message) { MessageHistory.Add(FDialogueMessage(messageType, message)); }

	bool GetIsHavePendingRequest() { return MessageHistory.Num() > 0; }
	TArray<UDialogueGraphResponseNodeInfo*> GetPendingRequest() { return PendingRequest; }
	void SetPendingRequest(TArray<UDialogueGraphResponseNodeInfo*> info) { PendingRequest = info; }
	void DeletePendingRequest() { PendingRequest.Empty(); }
protected:
	TArray<FDialogueMessage> MessageHistory;

	UPROPERTY()
	TArray<UDialogueGraphResponseNodeInfo*> PendingRequest;
};
