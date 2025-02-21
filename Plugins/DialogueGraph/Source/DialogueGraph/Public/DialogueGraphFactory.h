#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphFactory.generated.h"

UCLASS()
class UDialogueGraphFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogueGraphFactory(const FObjectInitializer& objectInitializer);

	//interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
};