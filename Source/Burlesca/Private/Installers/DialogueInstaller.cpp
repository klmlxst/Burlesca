#include "Installers/DialogueInstaller.h"

#include "Dialogue/DialoguePlayer.h"

ADialogueInstaller::ADialogueInstaller() { }

void ADialogueInstaller::InstallBindings(UDependencyContainer* Container)
{
	TArray<UDialogueGraphAsset*> dialogues;
	dialogues.Add(friendDialogueGraphAsset);
	
	dialoguePlayer = NewObject<UDialoguePlayer>(this);
	dialoguePlayer->Init();
	dialoguePlayer->ProvideDialoguesAssets(dialogues);

	dialogueSystemManager = NewObject<UDialogueSystemManager>(this);
	dialogueSystemManager->Init();
}
