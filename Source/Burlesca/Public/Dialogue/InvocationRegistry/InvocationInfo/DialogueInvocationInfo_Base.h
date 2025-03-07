#pragma once

#include "CoreMinimal.h"
#include "Dialogue/InvocationRegistry/DialogueInvocationParams.h"
#include "DialogueInvocationInfo_Base.generated.h"

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class BURLESCA_API UDialogueInvocationInfo_Base : public UObject
{
	GENERATED_BODY()

public:
	virtual FDialogueInvocationParams GetInvocationParams() { return FDialogueInvocationParams(); }
};