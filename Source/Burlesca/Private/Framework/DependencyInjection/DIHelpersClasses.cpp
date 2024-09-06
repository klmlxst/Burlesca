// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/DependencyInjection/DIHelpersClasses.h"
#include "Framework/DependencyInjection/DependencyContainer.h"


/*----------- Bind Info -----------*/

UBindInfo::UBindInfo(): FromBindClass(nullptr), ToBindClass(nullptr), Container(nullptr)
{
}


/*----------- From Binder -----------*/


UFromBinder::UFromBinder(): BindInfo(nullptr)
{
}


/**
 * @brief Use this function if you want to bind a new object to container.
 * Use To<T>() function after to choose class of object that will be created.
 */
UToBinder* UFromBinder::FromNew() const
{
	UToBinder* ToBinder = NewObject<UToBinder>();
	ToBinder->Init(this->BindInfo);
	return ToBinder;
}


/**
 * @brief Use this function if you want to bind an already created object to container.
 * If you binding interface then your object class must implement this interface.
 */
void UFromBinder::FromInstance(UObject* Object) const
{
	BindInfo->Container->Register(BindInfo->FromBindClass, Object);
}


/*----------- To Binder -----------*/


UToBinder::UToBinder(): BindInfo(nullptr)
{
}


/**
* @brief Don't use this function.
* It`s internal framework function.
* Use To...() instead.
*/
void UToBinder::Init(UBindInfo* bindInfo)
{
	this->BindInfo = bindInfo;
}

template <typename T>
void UToBinder::To()
{
	{
		BindInfo->ToBindClass = T::StaticClass();
		if(BindInfo->FromBindClass->IsChildOf(UInterface::StaticClass()))
		{
			if(!BindInfo->ToBindClass->ImplementsInterface(BindInfo->FromBindClass))
			{
				UE_LOG(LogTemp, Error, TEXT("%s class don`t inplements %s interface"), *BindInfo->ToBindClass->GetName(),*BindInfo->FromBindClass->GetName());
				return;
			}
		}
		BindInfo->Container->Register(BindInfo->FromBindClass, NewObject<T>(BindInfo->Container));
	}
}
