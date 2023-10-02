// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Items/ItemComponent.h"

DEFINE_LOG_CATEGORY(LogItemComponent);

UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeItem(Quantity);

	// NOTE(jejikeh): Maybe add logic for handling not only components, but also actors
	auto InteractionComponents = GetOwner()->GetComponentsByInterface(UInteractionInterface::StaticClass());

	if (InteractionComponents.IsEmpty())
	{
		UE_LOG(LogItemComponent, Error, TEXT("Owner does not have components implementing IInteractionInterface"));
	}
	else
	{
		InteractionObject = InteractionComponents.Last();
	}
}

void UItemComponent::InitializeItem(const int32 InQuantity)
{
	if (ItemDataTable && !ItemId.IsNone())
	{
		if (FItemData* ItemData = ItemDataTable->FindRow<FItemData>(ItemId, ItemId.ToString()))
		{
			ItemReference = NewObject<UItemBase>(GetOwner(), UItemBase::StaticClass());

			ItemReference->Data->ItemData = ItemData;
		}
	}
}

void UItemComponent::InitializeDrop(UItemBase* Item, const int32 InQuantity)
{
}

void UItemComponent::ItemActivatedByInteraction(AActor* InteractActor)
{
}

void UItemComponent::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Name = ItemReference->Data->ItemData->TextData.Name;
	InstanceInteractableData.Description = ItemReference->Data->ItemData->TextData.Description;
	InstanceInteractableData.Action = ItemReference->Data->ItemData->TextData.InteractText;
	InstanceInteractableData.Quantity = ItemReference->Data->Quantity;

	InteractionObject->InteractableData = InstanceInteractableData;
}

