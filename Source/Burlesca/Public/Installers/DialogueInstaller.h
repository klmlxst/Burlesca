#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphAsset.h"
#include "Dialogue/DialogueSystemManager.h"
#include "Framework/DependencyInjection/Inject.h"
#include "Framework/DependencyInjection/InjectionInstaller.h"
#include "DialogueInstaller.generated.h"

class UDialoguePlayer;

UCLASS()
class BURLESCA_API ADialogueInstaller : public AInjectionInstaller
{
	GENERATED_BODY()

public:
	virtual void InstallBindings(UDependencyContainer* Container) override;
	virtual void Start(UDependencyContainer* Container) override;
	
protected:
	UPROPERTY(EditAnywhere)
	float betweenMessageDelay = 1.0f;

	UPROPERTY()
	UDialoguePlayer* dialoguePlayer = nullptr;
	
	UPROPERTY()
	UDialogueSystemManager* dialogueSystemManager = nullptr;

	UPROPERTY()
	UConditionRegistry* conditionRegistry = nullptr;
	
	UPROPERTY(EditAnywhere)
	UDialogueGraphAsset* friendDialogueGraphAsset = nullptr;
	
	UPROPERTY(EditAnywhere)
    UDialogueGraphAsset* payerDialogueGraphAsset = nullptr;
};

