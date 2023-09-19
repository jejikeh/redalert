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

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemData ItemData;

	UPROPERTY(VisibleAnywhere, Category = "Item Data", meta=(UIMin=1, UIMax=100))
	int32 Quantity;
};

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
#pragma region Properties

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemBaseData Data;

#pragma endregion Properites

#pragma region Functions

	UItemBase();

	UItemBase* Copy() const;

	UFUNCTION(Category = "Inventory System | Item")
	FORCEINLINE float GetItemStackWeight() const
	{
		return Data.ItemData.NumericData.Weight * Data.Quantity;
	};

	UFUNCTION(Category = "Inventory System | Item")
	FORCEINLINE float GetItemWeight() const
	{
		return Data.ItemData.NumericData.Weight;
	}

	UFUNCTION(Category = "Inventory System | Item")
	FORCEINLINE bool IsFullStack() const
	{
		return Data.Quantity >= Data.ItemData.NumericData.MaxStackSize;
	}

	UFUNCTION(Category = "Inventory System | Item")
	void SetQuantity(const int32 Quantity);

	UFUNCTION(Category = "Inventory System | Item")
	virtual void Use(ACharacter* Character);

#pragma endregion Functions

protected:
#pragma region Function

	// NOTE: this is for [TArray::Search] overload implementation
	bool operator==(const FName& OtherId) const
	{
		return Data.ItemData.Id == OtherId;
	}

#pragma endregion Function
};
