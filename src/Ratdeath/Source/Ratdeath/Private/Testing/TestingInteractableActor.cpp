// Fill out your copyright notice in the Description page of Project Settings.


#include "Testing/TestingInteractableActor.h"

// Sets default values
ATestingInteractableActor::ATestingInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	InteractableOutlineComponent = CreateDefaultSubobject<UInteractableOutlineComponent>(TEXT("InteractOutlineComponent"));
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
