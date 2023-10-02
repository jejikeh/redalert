// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractableOutlineComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInteractableOutlineComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	UInteractableOutlineComponent();

	UFUNCTION(BlueprintCallable)
	void SetOutline(bool bIsOutline) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMeshComponent* OwnerMesh;
};
