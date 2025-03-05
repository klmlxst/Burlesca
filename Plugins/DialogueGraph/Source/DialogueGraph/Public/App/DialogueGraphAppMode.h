#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FDialogueGraphApp;

class FDialogueGraphAppMode : public FApplicationMode
{
public:
	FDialogueGraphAppMode(TSharedPtr<FDialogueGraphApp> app);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> inTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	TWeakPtr<FDialogueGraphApp> _app;
	FWorkflowAllowedTabSet _tabs;
};
