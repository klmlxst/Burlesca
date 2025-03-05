#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EConditionType : uint16
{
	None,
	IsGuitarSetUp UMETA(DisplayName = "Is Guitar Set Up", ToolTip = "True when guitar is set up"),
};