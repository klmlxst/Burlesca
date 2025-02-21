#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeType.generated.h"

UENUM()
enum class EDialogueGraphNodeType
{
	Unknown,
	StartNode,
	QuoteNode,
	EndNode,
	RequestNode,
	ResponseNode,
	InvokeNode
};