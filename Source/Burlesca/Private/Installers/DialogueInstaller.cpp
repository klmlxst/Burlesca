#include "Installers/DialogueInstaller.h"

#include "Dialogue/DialoguePlayer.h"

void ADialogueInstaller::InstallBindings(UDependencyContainer* Container)
{
	dialoguePlayer = NewObject<UDialoguePlayer>(this);
	dialogueSystemManager = NewObject<UDialogueSystemManager>(this);
	conditionRegistry = NewObject<UConditionRegistry>(this);
	
	Container->Bind<UDialogueSystemManager>()->FromInstance(dialogueSystemManager);
	Container->Bind<UConditionRegistry>()->FromInstance(conditionRegistry);
}

void ADialogueInstaller::Start(UDependencyContainer* Container)
{
	TArray<UDialogueGraphAsset*> dialogues;
	dialogues.Add(friendDialogueGraphAsset);
	dialogues.Add(payerDialogueGraphAsset);
	
	dialoguePlayer->ProvideDialoguesAssets(dialogues);

	dialogueSystemManager->Init(dialoguePlayer);
	
	dialoguePlayer->Init(betweenMessageDelay);
}
