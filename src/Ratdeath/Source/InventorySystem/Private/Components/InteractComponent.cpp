// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractComponent.h"

DEFINE_LOG_CATEGORY(LogInteractComponent);

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = GetOwner();
	if (UKismetSystemLibrary::DoesImplementInterface(Owner, UInteractTracing::StaticClass()))
	{
		OwnerInteractTracing = Owner;
	}
	else
	{
		UE_LOG(LogInteractComponent, Error, TEXT("Owner does not implement IInteractTracing"));
	}
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionDuration) > InteractionData.InteractionCheckFrequency)
	{
		const auto Interactable = FindInteractionActorFromView();
		if (!Interactable)
		{
			ClearInteractableData();
		}
		else
		{
			if (InteractionData.Interactable && Interactable != InteractionData.Interactable)
			{
				UnFocusCurrentInteraction();
			}
			
			FillInteractableData(Interactable);
			FocusCurrentInteraction();
			StartInteracting();
		}
	}
}

AActor* UInteractComponent::FindInteractionActorFromView()
{
	if (!OwnerInteractTracing)
	{
		return nullptr;
	}

	InteractionData.LastInteractionDuration = GetWorld()->GetTimeSeconds();
	FVector TraceStart{IInteractTracing::Execute_GetTraceStartVector(OwnerInteractTracing.GetObject())};

	FRotator TraceRotation = IInteractTracing::Execute_GetTraceRotation(OwnerInteractTracing.GetObject());
	FVector TraceEnd{TraceStart + TraceRotation.Vector() * InteractionData.InteractionCheckDistance};

	// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 2.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	if (FHitResult Hit; GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			const float Distance = (TraceStart - Hit.ImpactPoint).Size();

			if (Distance < InteractionData.InteractionCheckDistance)
			{
				return HitActor;
			}
		}
	}

	return nullptr;
}

void UInteractComponent::FillInteractableData(AActor* Interactable)
{
	if (IsInteracting())
	{
		EndInteracting();
	}

	// If we hit the same actor, do nothing
	if (Interactable == InteractionData.Interactable)
	{
		return;
	}
	
	InteractionData.SetInteractionObject(Interactable);
	InteractionData.LastInteractionDuration = GetWorld()->GetTimeSeconds();
}

void UInteractComponent::FocusCurrentInteraction() const
{
	// In case we don't have an object but still hold reference
	if (InteractionData.InteractionObject && IsValid(InteractionData.InteractionObject.GetObject()))
	{
		IInteractionInterface::Execute_BeginFocus(InteractionData.InteractionObject.GetObject());
	}
}

void UInteractComponent::UnFocusCurrentInteraction() const
{
	// In case we don't have an object but still hold reference
	if (InteractionData.InteractionObject && IsValid(InteractionData.InteractionObject.GetObject()))
	{
		IInteractionInterface::Execute_EndFocus(InteractionData.InteractionObject.GetObject());
	}
}

void UInteractComponent::ClearInteractableData()
{
	if (IsInteracting())
	{
		GetWorld()->GetTimerManager().ClearTimer(InteractionData.InteractionCheckTimerHandle);
	}

	UnFocusCurrentInteraction();

	InteractionData.ClearInteractionObject();
}

void UInteractComponent::StartInteracting()
{
	if (InteractionData.InteractionObject &&
		InteractionData.Interactable &&
		IsValid(InteractionData.InteractionObject.GetObject()))
	{
		IInteractionInterface::Execute_BeginInteract(InteractionData.InteractionObject.GetObject());

		if (FMath::IsNearlyZero(InteractionData.InteractionObject->InteractableData.InteractionDuration, 0.1f))
		{
			HandleInteraction();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(
				InteractionData.InteractionCheckTimerHandle,
				this,
				&UInteractComponent::HandleInteraction,
				1.0f,
				false);
		}
	}
}

void UInteractComponent::EndInteracting()
{
	GetWorld()->GetTimerManager().ClearTimer(InteractionData.InteractionCheckTimerHandle);

	if (IsValid(InteractionData.InteractionObject.GetObject()))
	{
		IInteractionInterface::Execute_EndInteract(InteractionData.InteractionObject.GetObject());
	}
}

void UInteractComponent::HandleInteraction()
{
	GetWorld()->GetTimerManager().ClearTimer(InteractionData.InteractionCheckTimerHandle);

	if (IsValid(InteractionData.InteractionObject.GetObject()))
	{
		IInteractionInterface::Execute_Interact(InteractionData.InteractionObject.GetObject());
	}
}
