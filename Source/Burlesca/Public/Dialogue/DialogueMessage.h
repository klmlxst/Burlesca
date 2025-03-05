// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueMessage.generated.h"

UENUM()
enum class EMessageType
{
	Send,
	Recieved
};

USTRUCT(BlueprintType)
struct BURLESCA_API FDialogueMessage
{
	GENERATED_BODY()

public:
	FDialogueMessage() {}
	FDialogueMessage(EMessageType type, const FText text) : MessageType(type), Message(text) {}
	void Init(EMessageType messageType, FText message)
	{
		MessageType = messageType;
		Message = message;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMessageType MessageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message;
};
