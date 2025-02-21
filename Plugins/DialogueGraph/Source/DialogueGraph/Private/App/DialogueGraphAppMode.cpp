#include "App/DialogueGraphAppMode.h"
#include "App/DialogueGraphApp.h"
#include "DialogueGraphPrimaryTabFactory.h"
#include "DialogueGraphPropertiesTabFactory.h"

FDialogueGraphAppMode::FDialogueGraphAppMode(TSharedPtr<FDialogueGraphApp> app) : FApplicationMode(TEXT("DialogueGraphAppMode"))
{
	_app = app;

	_tabs.RegisterFactory(MakeShareable(new FDialogueGraphPrimaryTabFactory(app)));
	_tabs.RegisterFactory(MakeShareable(new FDialogueGraphPropertiesTabFactory(app)));

	TabLayout = FTabManager::NewLayout("DialogueGraphAppMode_Layout_v1")->
	AddArea (
		FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split (
				FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->Split (
						FTabManager::NewStack()
							->SetSizeCoefficient(0.75)
							->AddTab(FName(TEXT("DialogueGraphPrimaryTab")), ETabState::OpenedTab)
					)
					->Split (
						FTabManager::NewStack()
							->SetSizeCoefficient(0.25)
							->AddTab(FName(TEXT("DialogueGraphPropertiesTab")), ETabState::OpenedTab)
					)
			)
	);
}

void FDialogueGraphAppMode::RegisterTabFactories(TSharedPtr<FTabManager> inTabManager)
{
	TSharedPtr<FDialogueGraphApp> app = _app.Pin();
	app->PushTabFactories(_tabs);

	FApplicationMode::RegisterTabFactories(inTabManager);
}

void FDialogueGraphAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FDialogueGraphAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
