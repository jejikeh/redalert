// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

UItemBase::UItemBase()
{
}

UItemBase* UItemBase::Copy() const
{
	auto const Copy = NewObject<UItemBase>(StaticClass());

	Copy->Data = Data;

	return Copy;
}

void UItemBase::Use(ACharacter* Character)
{
}
