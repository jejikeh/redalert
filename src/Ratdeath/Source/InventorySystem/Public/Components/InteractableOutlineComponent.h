// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractableOutlineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndInteract);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInteractableOutlineComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	UInteractableOutlineComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginFocus_Implementation() override;

	virtual void BeginInteract_Implementation() override;

	virtual void EndFocus_Implementation() override;
	
	virtual void EndInteract_Implementation() override;

	virtual void Interact_Implementation(AActor* InteractActor) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* OwnerMesh;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FOnInteract OnInteract;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FBeginInteract BeginInteract;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FEndInteract EndInteract;

	UPROPERTY(EditInstanceOnly, Category = "Inventory System")
	FInteractableData InstanceInteractableData;
};
