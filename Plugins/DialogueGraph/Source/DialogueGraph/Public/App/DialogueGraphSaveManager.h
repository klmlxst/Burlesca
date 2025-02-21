#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphSaveManager.generated.h"

class UDialogueGraphAsset;

USTRUCT(BlueprintType)
struct FDialogueGraphSaveManager
{
	GENERATED_BODY()

public:
	static void SaveGraph(UDialogueGraphAsset* asset, UEdGraph* graph);
	static void LoadGraph(UDialogueGraphAsset* asset, UEdGraph* graph);
};
