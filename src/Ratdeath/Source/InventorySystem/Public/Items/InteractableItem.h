// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractableItem.generated.h"

class UInteractableOutlineComponent;
class UInteractableComponent;

UCLASS()
class INVENTORYSYSTEM_API AInteractableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableItem();
	
	void InitializePick();

	// TODO(jejikeh): Maybe is better to keep Asset Reference to DataTable
	void InitializeDrop(UItemBase* ItemToDrop);

	FORCEINLINE UItemBase* GetItemData() const { return ItemData; }


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Inventory System | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere, Category = "Inventory System | Components")
	UInteractableComponent* InteractableComponent;

	UPROPERTY(EditAnywhere, Category = "Inventory System | Components")
	UInteractableOutlineComponent* InteractableOutlineComponent;

	UPROPERTY(EditInstanceOnly, Category = "Inventory System | Item Data")
	UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Inventory System | Item Data")
	FName ReferencedRowItemId;

	UPROPERTY(VisibleAnywhere, Category = "Inventory System | Item Reference")
	UItemBase* ItemData;

	UPROPERTY(VisibleInstanceOnly, Category = "Inventory System | Interaction")
	FInteractableData InstanceInteractableData;

	virtual void Interact(AActor* InteractActor);

	virtual EInteractableType GetInteractableType();

	// TODO(jejikeh): Replace Actor with Inventory Component

	UFUNCTION()
	void TakeItem(AActor* InteractActor);

	void UpdateInteractableDataInComponent();
	
	void TurnOnOutline();
	
	void TurnOffOutline();
};
