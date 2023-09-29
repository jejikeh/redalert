// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableOutlineComponent.h"

UInteractableOutlineComponent::UInteractableOutlineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableOutlineComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const auto OwnerMeshComponent = GetOwner()->GetComponentByClass<UStaticMeshComponent>())
	{
		OwnerMesh = OwnerMeshComponent;
	}

	InteractableData = InstanceInteractableData;
}

void UInteractableOutlineComponent::BeginFocus_Implementation()
{
	if (OwnerMesh)
	{
		OwnerMesh->SetRenderCustomDepth(true);
	}
}

void UInteractableOutlineComponent::EndFocus_Implementation()
{
	if (OwnerMesh)
	{
		OwnerMesh->SetRenderCustomDepth(false);
	}
}

void UInteractableOutlineComponent::EndInteract_Implementation()
{
	EndInteract.Broadcast();
}

void UInteractableOutlineComponent::BeginInteract_Implementation()
{
	BeginInteract.Broadcast();
}

void UInteractableOutlineComponent::Interact_Implementation(AActor* InteractActor)
{
	OnInteract.Broadcast(InteractActor);
}

void UInteractableOutlineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

