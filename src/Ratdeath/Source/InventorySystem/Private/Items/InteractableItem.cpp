// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InteractableItem.h"

#include "Components/InteractableComponent.h"
#include "Components/InteractableOutlineComponent.h"

// Sets default values
AInteractableItem::AInteractableItem()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickMesh"));
	PickupMesh->SetSimulatePhysics(true);
	SetRootComponent(PickupMesh);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableOutlineComponent = CreateDefaultSubobject<UInteractableOutlineComponent>(
		TEXT("InteractableOutlineComponent"));
}

void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();

	InitializePick();

	InteractableComponent->BeginFocus.AddDynamic(this, &AInteractableItem::TurnOnOutline);
	InteractableComponent->EndFocus.AddDynamic(this, &AInteractableItem::TurnOffOutline);
}

void AInteractableItem::InitializePick()
{
	if (ItemDataTable && !ReferencedRowItemId.IsNone())
	{
		if (const auto ItemReference = ItemDataTable->FindRow<FItemData>(ReferencedRowItemId, ReferencedRowItemId.ToString()))
		{
			ItemData = NewObject<UItemBase>(this, UItemBase::StaticClass());
			ItemData->Data->ItemData = ItemReference;
			
			PickupMesh->SetStaticMesh(ItemData->Data->ItemData->AssetData.Mesh);

			UpdateInteractableDataInComponent();
		}
	}
}

void AInteractableItem::InitializeDrop(UItemBase* ItemToDrop)
{
	ItemData = ItemToDrop;
	PickupMesh->SetStaticMesh(ItemData->Data->ItemData->AssetData.Mesh);
	UpdateInteractableDataInComponent();
}

void AInteractableItem::Interact(AActor* InteractActor)
{
	if (InteractActor)
	{
		TakeItem(InteractActor);
	}
}

void AInteractableItem::TakeItem(AActor* InteractActor)
{
	if (!IsValid(this))
	{
		if (ItemData)
		{
			// TODO(jejikeh): Logic with inventory component
			// InteractableComponent->Interact(InteractActor);
		}
	}
}

EInteractableType AInteractableItem::GetInteractableType()
{
	return EInteractableType::Pickup;
}

void AInteractableItem::UpdateInteractableDataInComponent()
{
	InstanceInteractableData.InteractableType = GetInteractableType();
	InstanceInteractableData.Name = ItemData->Data->ItemData->TextData.Name;
	InstanceInteractableData.Action = ItemData->Data->ItemData->TextData.InteractText;
	InstanceInteractableData.Description = ItemData->Data->ItemData->TextData.Description;

	InteractableComponent->InteractableData = InstanceInteractableData;
}

void AInteractableItem::TurnOnOutline()
{
	InteractableOutlineComponent->SetOutline(true);
}

void AInteractableItem::TurnOffOutline()
{
	InteractableOutlineComponent->SetOutline(false);
}
