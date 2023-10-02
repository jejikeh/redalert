// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndInteract);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginFocus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndFocus);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInteractableComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	UInteractableComponent();

	virtual void BeginFocus_Implementation() override;

	virtual void BeginInteract_Implementation() override;

	virtual void EndFocus_Implementation() override;
	
	virtual void EndInteract_Implementation() override;

	virtual void Interact_Implementation(AActor* InteractActor) override;

	UPROPERTY(EditInstanceOnly, Category = "Inventory System")
	FInteractableData InstanceInteractableData;
	
	UPROPERTY(BlueprintAssignable, Category = "Inventory System | Events")
	FOnInteract OnInteract;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System | Events")
	FBeginInteract BeginInteract;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System | Events")
	FEndInteract EndInteract;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System | Events")
	FBeginFocus BeginFocus;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System | Events")
	FEndFocus EndFocus;

protected:
	virtual void BeginPlay() override;
};
