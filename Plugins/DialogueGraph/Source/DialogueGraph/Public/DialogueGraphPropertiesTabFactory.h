#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FDialogueGraphPropertiesTabFactory : public FWorkflowTabFactory
{
public:
	FDialogueGraphPropertiesTabFactory(TSharedPtr<class FDialogueGraphApp> app);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<FDialogueGraphApp> _app;
};
