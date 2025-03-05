#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeInfo_Base.h"
#include "ConditionsRegistry/ConditionType.h"
#include "ConditionsRegistry/ConditionInfo/ConditionInfo_Base.h"
#include "DialogueGraphResponseNodeInfo.generated.h"

enum class EConditionType : uint16;

UCLASS(BlueprintType)
class DIALOGUEGRAPHRUNTIME_API UDialogueGraphResponseNodeInfo : public UDialogueGraphNodeInfo_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText ResponseText;

	UPROPERTY(EditAnywhere)
	bool bHasCondition;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition = "bHasCondition"))
	EConditionType Condition = EConditionType::None;

	UPROPERTY(EditAnywhere, meta=(EditCondition = "bHasCondition && Condition != EConditionType::None"))
	FText ConditionTooltip;
	
	UPROPERTY(EditAnywhere, Instanced, meta=(EditCondition = "Condition != EConditionType::None"), export)
	UConditionInfo_Base* ConditionInfo;

	bool bAreConditionsMet = true;
	bool bIsAlreadyShown = false;
	
protected:
	void OnConditionTypeChanged()
	{
		if(ConditionInfo)	
		{
			ConditionInfo->MarkAsGarbage();
			ConditionInfo = nullptr;	
		}
		
		switch (Condition)
		{
			case EConditionType::IsGuitarSetUp:
				ConditionInfo = NewObject<UConditionInfo_Base>(GetOuter());
				break;
			default:
				ConditionInfo = NewObject<UConditionInfo_Base>(GetOuter());
				break;
		}
	}
	
#if WITH_EDITOR
	virtual void PostInitProperties() override
	{
		Super::PostInitProperties();
		
		ConditionInfo = NewObject<UConditionInfo_Base>(GetOuter());
	}
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);

		if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UDialogueGraphResponseNodeInfo, Condition))
		{
			OnConditionTypeChanged();
		}
	}
#endif
};
	