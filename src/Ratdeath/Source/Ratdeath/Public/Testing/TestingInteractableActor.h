// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "TestingInteractableActor.generated.h"

UCLASS()
class RATDEATH_API ATestingInteractableActor : public AActor, public IInteractionInterface
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
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void BeginFocus_Implementation() override;
	
	virtual void BeginInteract_Implementation() override;
	
	virtual void EndFocus_Implementation() override;
	
	virtual void EndInteract_Implementation() override;
	
	virtual void Interact_Implementation() override;
};
