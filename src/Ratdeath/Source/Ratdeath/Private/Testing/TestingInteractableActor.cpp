// Fill out your copyright notice in the Description page of Project Settings.


#include "Testing/TestingInteractableActor.h"

// Sets default values
ATestingInteractableActor::ATestingInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ATestingInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATestingInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestingInteractableActor::BeginFocus_Implementation()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void ATestingInteractableActor::EndFocus_Implementation()
{
	if (Mesh)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void ATestingInteractableActor::BeginInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Interact"));
}

void ATestingInteractableActor::EndInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End Interact"));
}

void ATestingInteractableActor::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
}

