// Fill out your copyright notice in the Description page of Project Settings.


#include "Testing/TestingInteractableActor.h"

#include "Components/InteractableComponent.h"
#include "Components/InteractableOutlineComponent.h"

// Sets default values
ATestingInteractableActor::ATestingInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	InteractableOutlineComponent = CreateDefaultSubobject<UInteractableOutlineComponent>(TEXT("InteractOutlineComponent"));
	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
}

// Called when the game starts or when spawned
void ATestingInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->BeginFocus.AddDynamic(this, &ATestingInteractableActor::TurnOnOutline);
	InteractableComponent->EndFocus.AddDynamic(this, &ATestingInteractableActor::TurnOffOutline);
}

void ATestingInteractableActor::TurnOnOutline()
{
	InteractableOutlineComponent->SetOutline(true);
}

void ATestingInteractableActor::TurnOffOutline()
{
	InteractableOutlineComponent->SetOutline(false);
}

void ATestingInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
