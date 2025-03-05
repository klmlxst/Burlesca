#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphAsset.generated.h"

class UDialogueGraphRuntimeNode;
class UDialogueGraphRuntimeGraph;

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphAsset : public UObject
{
	GENERATED_BODY()

public:
	bool bIsDialogueActive = false;
	
	UPROPERTY(EditAnywhere)
	FString DialogueName  = TEXT("Enter dialogue name here");
	
	UPROPERTY()
	UDialogueGraphRuntimeGraph* Graph = nullptr;
};

