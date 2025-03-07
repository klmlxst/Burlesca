// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue/InvocationRegistry/DialogueInvocationRegistry.h"

#include "Dialogue/DialogueSystemManager.h"
#include "Dialogue/InvocationRegistry/DialogueInvocationParams.h"
#include "Dialogue/InvocationRegistry/DialogueInvocationType.h"
#include "Dialogue/InvocationRegistry/Invocations/ChangeObjectInteractionActivityStateDialogueInvocation.h"

void UDialogueInvocationRegistry::Inject(UDependencyContainer* Container)
{
	UChangeObjectInteractionActivityStateDialogueInvocation* changeObjectActivityStateInvocation =
		NewObject<UChangeObjectInteractionActivityStateDialogueInvocation>(this);
	changeObjectActivityStateInvocation->InitDependenciesFromDIContainer(Container);
	Invocations.Add(EDialogueInvocationType::ChangeObjectInteractionActivityState, changeObjectActivityStateInvocation);
}

void UDialogueInvocationRegistry::Invoke(EDialogueInvocationType invocationType, FDialogueInvocationParams params)
{
	UObject** objPtr = Invocations.Find(invocationType);
	if(objPtr)
	{
		UObject* obj = *objPtr;
		if(obj)
		{
			IDialogueInvocation* condition = Cast<IDialogueInvocation>(obj);
			condition->Invoke(params);
		}
	}
    
	UE_LOG(DialogueGraphRuntime, Error, TEXT("No condition with name: %d was found"), invocationType);
}
