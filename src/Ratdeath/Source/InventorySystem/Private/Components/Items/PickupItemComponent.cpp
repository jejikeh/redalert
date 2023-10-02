// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Items/PickupItemComponent.h"

UPickupItemComponent::UPickupItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPickupItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPickupItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

