#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"

class SDialogueGraphQuoteNodePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphQuoteNodePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override { return FLinearColor::Blue; }
};

class SDialogueGraphStartNodePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphStartNodePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override { return FLinearColor::Green; }
};

class SDialogueGraphEndNodePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphEndNodePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override { return FLinearColor::Red; }
};

class SDialogueGraphRequestNodePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphRequestNodePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override { return FLinearColor(1, 0.3f, 0.1f); }
};

class SDialogueGraphResponseNodePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphResponseNodePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override { return FLinearColor(0.9f, 0.3f, 0); }
};

class SDialogueGraphInvokeNodePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphInvokeNodePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override { return FLinearColor::Yellow; }
};