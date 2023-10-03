// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

USTRUCT()
struct FItemBaseData
{
	GENERATED_BODY()

	FItemData* ItemData;
};

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	FItemBaseData* Data;

	UItemBase();

	UItemBase* Copy() const;
	
	UFUNCTION(Category = "Inventory System | Item")
	virtual void Use(ACharacter* Character);

protected:
	// NOTE: this is for [TArray::Search] overload implementation
	bool operator==(const FName& OtherId) const
	{
		return Data->ItemData->Id == OtherId;
	}
};
