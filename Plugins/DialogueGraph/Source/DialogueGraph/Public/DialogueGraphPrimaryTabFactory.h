#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FDialogueGraphPrimaryTabFactory : public FWorkflowTabFactory
{
public:
	FDialogueGraphPrimaryTabFactory(TSharedPtr<class FDialogueGraphApp> app);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<FDialogueGraphApp> _app;
};
