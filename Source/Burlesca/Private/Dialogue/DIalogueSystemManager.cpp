#include "Dialogue/DialogueSystemManager.h"
#include "Dialogue/DialoguePlayer.h"
#include "MobilePhone/MobilePhone.h"

DEFINE_LOG_CATEGORY(DialogueGraphRuntime)

void UDialogueSystemManager::Inject(UDependencyContainer* Container)
{
	MobilePhone = Container->Resolve<AMobilePhone>();
	ConditionRegistry = Container->Resolve<UConditionRegistry>();
}

void UDialogueSystemManager::Init(UDialoguePlayer* dialoguePlayer)
{
	DialoguePlayer = dialoguePlayer;
	ChatScreen = Cast<UChatScreen>(MobilePhone->GetApp(EPhoneApplication::Chat));

	FriendMessageHistory = NewObject<UMessageHistoryData>(this);
	PayerMessageHistory = NewObject<UMessageHistoryData>(this);
	MonsterMessageHistory = NewObject<UMessageHistoryData>(this);
	
	CompanionToHistoryMap.Add(EDialogueCompanion::Friend, FriendMessageHistory);
	CompanionToHistoryMap.Add(EDialogueCompanion::Payer, PayerMessageHistory);
	CompanionToHistoryMap.Add(EDialogueCompanion::Monster, MonsterMessageHistory);
	
	DialoguePlayer->OnMessageSend.AddDynamic(this, &UDialogueSystemManager::HandleMessageRecieved);
	DialoguePlayer->OnRequestSend.AddDynamic(this, &UDialogueSystemManager::HandleRequestRecieved);
	ChatScreen->OnCompanionSelected.AddDynamic(this, &UDialogueSystemManager::HandleCompanionSelected);
	ChatScreen->OnResponseSelected.AddDynamic(this, &UDialogueSystemManager::HandleResponseSelected);
}

void UDialogueSystemManager::HandleMessageRecieved(EDialogueCompanion companion, UDialogueGraphQuoteNodeInfo* info)
{
	FDialogueMessage message = FDialogueMessage(EMessageType::Recieved, info->DialogueText);
	
	if(SelectedCompanion != companion || !ChatScreen->GetIsDialogueWindowShown())
	{
		MobilePhone->PlayNotificationSound();
		ChatScreen->IncreaseUnreadMessagesQuantity(companion);
	}
	else
	{
		ChatScreen->CreateChatMessageWidget(message);
	}
	
	CompanionToHistoryMap[companion]->AddMessageToHistory(message);
}

void UDialogueSystemManager::HandleRequestRecieved(EDialogueCompanion companion, TArray<UDialogueGraphResponseNodeInfo*> info)
{
	if(companion == SelectedCompanion)
	{
		ModifyInfoWithConditionCheck(info);
		ChatScreen->ShowRequest(info);
	}
	
	CompanionToHistoryMap[companion]->SetPendingRequest(info);
}

void UDialogueSystemManager::ModifyInfoWithConditionCheck(TArray<UDialogueGraphResponseNodeInfo*> info)
{
	for(UDialogueGraphResponseNodeInfo* responseInfo : info)
	{
		if(responseInfo->bHasCondition)
		{
			if(!responseInfo->ConditionInfo)
			{
				UE_LOG(DialogueGraphRuntime, Error, TEXT("UDialogueSystemManager::ModifyInfoWithConditionCheck - Condition info is nullptr."))
				return;
			}
			
			if(!ConditionRegistry->CheckCondition(responseInfo->Condition, responseInfo->ConditionInfo->GetConditionParams()))
			{
				responseInfo->bAreConditionsMet = false;
			}
		}
	}
}

void UDialogueSystemManager::HandleResponseSelected(int responseId)
{
	FDialogueMessage message = FDialogueMessage(EMessageType::Send, CompanionToHistoryMap[SelectedCompanion]->GetPendingRequest()[responseId]->ResponseText);
	CompanionToHistoryMap[SelectedCompanion]->DeletePendingRequest();
	CompanionToHistoryMap[SelectedCompanion]->AddMessageToHistory(message);
	ChatScreen->ClearRequest();
	ChatScreen->CreateChatMessageWidget(message);
	DialoguePlayer->ResponseChoosed(SelectedCompanion, responseId);
}

void UDialogueSystemManager::HandleCompanionSelected(EDialogueCompanion companion)
{
	if(SelectedCompanion != companion)
	{
		SelectedCompanion = companion;
		ChatScreen->ClearRequest();
		ChatScreen->ClearDialogue();
		ChatScreen->LoadDialogue(CompanionToHistoryMap[companion]->GetMessageHistory());
		if(CompanionToHistoryMap[companion]->GetIsHavePendingRequest())
		{	
			ModifyInfoWithConditionCheck(CompanionToHistoryMap[companion]->GetPendingRequest());
			ChatScreen->ShowRequest(CompanionToHistoryMap[companion]->GetPendingRequest());
		}
	}
	
	ChatScreen->ShowDialogueWindow();
}
