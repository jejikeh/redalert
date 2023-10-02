// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableData = InstanceInteractableData;
}

void UInteractableComponent::BeginFocus_Implementation()
{
	BeginFocus.Broadcast();
}

void UInteractableComponent::BeginInteract_Implementation()
{
	BeginInteract.Broadcast();
}

void UInteractableComponent::EndFocus_Implementation()
{
	EndFocus.Broadcast();
}

void UInteractableComponent::EndInteract_Implementation()
{
	EndInteract.Broadcast();
}

void UInteractableComponent::Interact_Implementation(AActor* InteractActor)
{
	OnInteract.Broadcast(InteractActor);
}
