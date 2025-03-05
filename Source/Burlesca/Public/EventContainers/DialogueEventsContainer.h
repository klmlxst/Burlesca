#pragma once

#include "CoreMinimal.h"
#include "Dialogue/DialogueCompanion.h"
#include "DialogueEventsContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartDialogue, EDialogueCompanion, companion);
	
UCLASS()
class BURLESCA_API UDialogueEventsContainer : public UObject
{
	GENERATED_BODY()
	
public:
	FOnStartDialogue OnStartDialogue;

	
};