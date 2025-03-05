#include "Pins/DialogueGraphPinFactory.h"
#include "Pins/DialogueGraphPinsVariants.h"

TSharedPtr<SGraphPin> FDialogueGraphPinFactory::CreatePin(UEdGraphPin* pin) const
{
	if(pin->PinType.PinSubCategory == FName(TEXT("DialogueGraphQuoteNodePin")))
	{
		return SNew(SDialogueGraphQuoteNodePin, pin);
	}
	if(pin->PinType.PinSubCategory == FName(TEXT("DialogueGraphStartNodePin")))
	{
		return SNew(SDialogueGraphStartNodePin, pin);
	}
	if(pin->PinType.PinSubCategory == FName(TEXT("DialogueGraphEndNodePin")))
	{
		return SNew(SDialogueGraphEndNodePin, pin);
	}
	if(pin->PinType.PinSubCategory == FName(TEXT("DialogueGraphRequestNodePin")))
	{
		return SNew(SDialogueGraphRequestNodePin, pin);
	}
	if(pin->PinType.PinSubCategory == FName(TEXT("DialogueGraphResponseNodePin")))
	{
		return SNew(SDialogueGraphResponseNodePin, pin);
	}
	if(pin->PinType.PinSubCategory == FName(TEXT("DialogueGraphInvokeNodePin")))
	{
		return SNew(SDialogueGraphInvokeNodePin, pin);
	}

	return nullptr;
}
