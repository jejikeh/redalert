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

void UItemBase::SetQuantity(const int32 Quantity)
{
	if (Data.Quantity != Quantity)
	{
		auto const MaximumStackableSize = Data.ItemData.NumericData.bIsStackable
			                                  ? Data.ItemData.NumericData.MaxStackSize
			                                  : 1;

		Data.Quantity = FMath::Clamp(Quantity, 0, MaximumStackableSize);
	}
}

void UItemBase::Use(ACharacter* Character)
{
}
