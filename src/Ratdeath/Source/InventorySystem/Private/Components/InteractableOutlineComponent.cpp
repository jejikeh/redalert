// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableOutlineComponent.h"

UInteractableOutlineComponent::UInteractableOutlineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableOutlineComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerMesh = GetOwner()->GetComponentByClass<UMeshComponent>();
}

void UInteractableOutlineComponent::SetOutline(bool bIsOutline) const
{
	if (OwnerMesh)
	{
		OwnerMesh->SetRenderCustomDepth(bIsOutline);
	}
}

