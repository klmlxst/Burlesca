#pragma once

#include "CoreMinimal.h"

class UDialogueGraphAsset;

struct FDialogueGraphSaveManager
{
	static void SaveGraph(UDialogueGraphAsset* asset, UEdGraph* graph);
	static void LoadGraph(UDialogueGraphAsset* asset, UEdGraph* graph);
};
