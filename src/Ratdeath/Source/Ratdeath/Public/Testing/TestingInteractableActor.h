// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractableOutlineComponent.h"
#include "GameFramework/Actor.h"
#include "TestingInteractableActor.generated.h"

UCLASS()
class RATDEATH_API ATestingInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestingInteractableActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Testing")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Inventory System")
	UInteractableOutlineComponent* InteractableOutlineComponent;
	
	virtual void BeginPlay() override;
};
