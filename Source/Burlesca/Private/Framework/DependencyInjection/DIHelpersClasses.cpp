// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/DependencyInjection/DIHelpersClasses.h"

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
	UToBinder* ToBinder = NewObject<UToBinder>(this->BindInfo->Container);
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


/**
* @brief Don't use this function.
* It`s internal framework function.
* Use From...() instead.
*/
template <typename T>
void UFromBinder::Init(UDependencyContainer* Container)
{
	BindInfo = NewObject<UBindInfo>(this);
	BindInfo->FromBindClass = T::StaticClass;
	BindInfo->Container = Container;
}


/*----------- To Binder -----------*/


UToBinder::UToBinder(): BindInfo(nullptr)
{
}


/**
 * @brief Use this function to select object of what class must be created.
 * If you binding interface then your object class must implement this interface.
 *
 * @tparam T Created Object Class
 */
template <typename T>
void UToBinder::To()
{
	BindInfo->ToBindClass = T::StaticClass;
	if(BindInfo->FromBindClass->IsChildOf(UInterface::StaticClass()))
	{
		if(!BindInfo->ToBindClass->ImplementsInterface(BindInfo->FromBindClass))
		{
			UE_LOG(DependencyInjection, Error, TEXT("%s class don`t inplements %s interface"), *BindInfo->ToBindClass->GetName(),*BindInfo->FromBindClass->GetName());
			return;
		}
	}
	BindInfo->Container->Register(BindInfo->FromBindClass, NewObject<T>(BindInfo->Container));
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
