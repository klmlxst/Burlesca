#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EDialogueInvocationType : uint16
{
	None,
	ChangeObjectInteractionActivityState,
};