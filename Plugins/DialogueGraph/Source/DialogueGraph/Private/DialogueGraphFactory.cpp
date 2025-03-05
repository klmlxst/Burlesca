#include "DialogueGraphFactory.h"
#include "DialogueGraphAsset.h"


UDialogueGraphFactory::UDialogueGraphFactory(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	SupportedClass = UDialogueGraphAsset::StaticClass();
}

UObject* UDialogueGraphFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UDialogueGraphAsset* asset = NewObject<UDialogueGraphAsset>(InParent, InName, Flags);
	return asset;
}

bool UDialogueGraphFactory::CanCreateNew() const
{
	return true;
}
