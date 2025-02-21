#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphAsset.h"
#include "Dialogue/DialogueSystemManager.h"
#include "Framework/DependencyInjection/InjectionInstaller.h"
#include "DialogueInstaller.generated.h"

class UDialoguePlayer;

UCLASS()
class BURLESCA_API ADialogueInstaller : public AInjectionInstaller
{
	GENERATED_BODY()

public:
	ADialogueInstaller();

	virtual void InstallBindings(UDependencyContainer* Container) override;

protected:
	UPROPERTY()
	UDialoguePlayer* dialoguePlayer = nullptr;

	UPROPERTY()
	UDialogueSystemManager* dialogueSystemManager = nullptr;
	
	UPROPERTY(EditAnywhere)
	UDialogueGraphAsset* friendDialogueGraphAsset = nullptr;
};

