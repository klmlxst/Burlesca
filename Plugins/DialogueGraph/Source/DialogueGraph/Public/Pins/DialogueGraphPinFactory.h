#pragma once
#include "EdGraphUtilities.h"

class SGraphPin;

struct FDialogueGraphPinFactory : FGraphPanelPinFactory
{
public:
	virtual ~FDialogueGraphPinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* pin) const;
};
