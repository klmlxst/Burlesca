#pragma once

#include "CoreMinimal.h"
#include "DialogueCompanion.h"
#include "MessageHistoryData.h"
#include "Framework/DependencyInjection/Inject.h"
#include "MobilePhone/MobilePhone.h"
#include "MobilePhone/ApplicationWidgets/Chat/ChatScreen.h"
#include "ConditionsRegistry/ConditionRegistry.h"
#include "DialogueSystemManager.generated.h"




DECLARE_LOG_CATEGORY_EXTERN(DialogueGraphRuntime, Log, All)

class UConditionTooltip;
class UDialogueGraphQuoteNodeInfo;
class UDialoguePlayer;

UCLASS()
class BURLESCA_API UDialogueSystemManager : public UObject, public IInject
{
	GENERATED_BODY()

public:
	UDialogueSystemManager() {}
	void Init(UDialoguePlayer*  dialoguePlayer);
	virtual void Inject(UDependencyContainer* Container) override;

protected:
	UFUNCTION()
	void HandleMessageRecieved(EDialogueCompanion companion, UDialogueGraphQuoteNodeInfo* info);

	UFUNCTION()
	void HandleRequestRecieved(EDialogueCompanion companion, TArray<UDialogueGraphResponseNodeInfo*> info);
	void ModifyInfoWithConditionCheck(TArray<UDialogueGraphResponseNodeInfo*> info);
	
	UFUNCTION()
	void HandleResponseSelected(int responseId);

	UFUNCTION()
	void HandleCompanionSelected(EDialogueCompanion companion);
	
	UPROPERTY()
	UDialoguePlayer* DialoguePlayer = nullptr;

	UPROPERTY()
	AMobilePhone* MobilePhone = nullptr;
	
	UPROPERTY()
	UChatScreen* ChatScreen = nullptr;

	UPROPERTY()
	UConditionRegistry* ConditionRegistry = nullptr;
	
	UPROPERTY()
	EDialogueCompanion SelectedCompanion = EDialogueCompanion::None;
	
	// message history
	UPROPERTY()
	UMessageHistoryData* FriendMessageHistory = nullptr;

	UPROPERTY()
	UMessageHistoryData* PayerMessageHistory = nullptr;

	UPROPERTY()
	UMessageHistoryData* MonsterMessageHistory = nullptr;

	UPROPERTY()
	TMap<EDialogueCompanion, UMessageHistoryData*> CompanionToHistoryMap;
};