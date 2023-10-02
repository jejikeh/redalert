// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Interfaces/InteractionInterface.h"
#include "Items/ItemBase.h"
#include "ItemComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogItemComponent, Log, All);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UItemComponent();
	
	void InitializeItem(const int32 InQuantity);

	void InitializeDrop(UItemBase* Item, const int32 InQuantity);

	FORCEINLINE UItemBase* GetItemData() const { return ItemReference; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category = "Inventory System | Item Data")
	UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Inventory System | Item Data")
	FName ItemId;

	UPROPERTY(VisibleAnywhere, Category = "Inventory System | Item Data")
	UItemBase* ItemReference;

	UPROPERTY(EditInstanceOnly, Category = "Inventory System | Item Data")
	int32 Quantity;

	UPROPERTY(VisibleInstanceOnly, Category = "Inventory System | Item Data")
	FInteractableData InstanceInteractableData;

	UPROPERTY()
	TScriptInterface<IInteractionInterface> InteractionObject;

	virtual void ItemActivatedByInteraction(AActor* InteractActor);

	virtual void UpdateInteractableData();
};
