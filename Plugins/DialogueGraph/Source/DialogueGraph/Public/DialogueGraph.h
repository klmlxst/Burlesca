// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct FDialogueGraphPinFactory;

class FDialogueGraphModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FSlateStyleSet> _styleSet = nullptr;
	TSharedPtr<FDialogueGraphPinFactory> _pinFactory = nullptr;
};
