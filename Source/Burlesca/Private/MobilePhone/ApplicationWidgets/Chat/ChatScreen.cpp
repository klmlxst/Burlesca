// Fill out your copyright notice in the Description page of Project Settings.

#include "MobilePhone/ApplicationWidgets/Chat/ChatScreen.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/Spacer.h"
#include "Dialogue/DialogueSystemManager.h"

void UChatScreen::Inject(UDependencyContainer* Container)
{
}

auto UChatScreen::SetupInput(UEnhancedInputComponent* input) -> void
{
	Super::SetupInput(input);
}

void UChatScreen::NativeConstruct()
{
	Super::NativeConstruct();

	CompanionToButtonMap.Add(EDialogueCompanion::Friend, FriendButton);
	CompanionToButtonMap.Add(EDialogueCompanion::Payer, PayerButton);
	CompanionToButtonMap.Add(EDialogueCompanion::Monster, MonsterButton);
	
	FriendButton->OnSelected.AddDynamic(this, &UChatScreen::ProcessOnCompanionSelected);
	PayerButton->OnSelected.AddDynamic(this, &UChatScreen::ProcessOnCompanionSelected);
	MonsterButton->OnSelected.AddDynamic(this, &UChatScreen::ProcessOnCompanionSelected);

	FriendButton->ShowWidget();
	PayerButton->ShowWidget();
	MonsterButton->HideWidget();
}

void UChatScreen::CloseApplication()
{
	Super::CloseApplication();

	HideDialogueWindow();
}

void UChatScreen::LoadDialogue(TArray<FDialogueMessage> messageHistory)
{
	USpacer* chatSpacer = NewObject<USpacer>(MessagePlaceholder);
	MessagePlaceholder->AddChild(chatSpacer);
	Cast<UScrollBoxSlot>(chatSpacer->Slot)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	
	for(FDialogueMessage message : messageHistory)
	{
		CreateChatMessageWidget(message);
	}
}

void UChatScreen::CreateChatMessageWidget(FDialogueMessage message)
{
	UChatMessage* chatMessage = CreateWidget<UChatMessage>(GetWorld(), ChatMessageClass);
	chatMessage->Init(message.Message, message.MessageType);
	MessagePlaceholder->AddChild(chatMessage);
	MessagePlaceholder->ScrollToEnd();

	if(message.MessageType == EMessageType::Recieved)
	{
		Cast<UScrollBoxSlot>(chatMessage->Slot)->SetHorizontalAlignment(HAlign_Left);
	}
	else
	{
		Cast<UScrollBoxSlot>(chatMessage->Slot)->SetHorizontalAlignment(HAlign_Right);
	}
}

void UChatScreen::IncreaseUnreadMessagesQuantity(EDialogueCompanion companion)
{
	CompanionToButtonMap[companion]->IncreaseUnreadMessagesQuantity();
}

void UChatScreen::ShowRequest(TArray<UDialogueGraphResponseNodeInfo*> info)
{	
	for(int i = 0; i < info.Num(); i++)
	{
		UDialogueResponseButton* responseButton = CreateWidget<UDialogueResponseButton>(GetWorld(), DialogueResponseButtonClass);
		responseButton->Init(info[i], i);
		if(!info[i]->bAreConditionsMet)
		{
			responseButton->OnConditonTooltipShow.AddDynamic(this, &UChatScreen::ShowConditionTooltip);
			responseButton->OnConditonTooltipHide.AddDynamic(this, &UChatScreen::HideConditionTooltip);
		}
		ResponsePlaceholder->AddChild(responseButton);
		responseButton->OnResponseSelected.AddDynamic(this, &UChatScreen::ProcessOnResponseSelected);
	}
}

//Cast<UScrollBoxSlot>(responseButton->Slot)->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

void UChatScreen::ClearDialogue() { MessagePlaceholder->ClearChildren(); }

void UChatScreen::ClearRequest() { ResponsePlaceholder->ClearChildren(); }

void UChatScreen::ProcessOnResponseSelected(int responseId)
{
	OnResponseSelected.Broadcast(responseId);
	for(UWidget* responseButton : ResponsePlaceholder->GetAllChildren())
	{
		Cast<UDialogueResponseButton>(responseButton)->OnResponseSelected.RemoveDynamic(this, &UChatScreen::ProcessOnResponseSelected);
	}

	ResponsePlaceholder->ClearChildren();
}
