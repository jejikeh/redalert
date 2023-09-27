// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "Interfaces/InteractTracing.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InteractComponent.generated.h"


class IInteractionInterface;

USTRUCT(BlueprintType)
struct FInteractionData
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Interactable;

	UPROPERTY()
	float InteractionDuration;

	UPROPERTY()
	float LastInteractionDuration;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TScriptInterface<IInteractionInterface> InteractionObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckFrequency;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	double InteractionCheckDistance;

	FTimerHandle InteractionCheckTimerHandle;

	void SetInteractionObject(AActor* InteractableObject)
	{
		Interactable = InteractableObject;
		if (UKismetSystemLibrary::DoesImplementInterface(InteractableObject, UInteractionInterface::StaticClass()))
		{
			InteractionObject = InteractableObject;
		}
	}

	void ClearInteractionObject()
	{
		Interactable = nullptr;
		InteractionObject = nullptr;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FInteractionData InteractionData;
	
	FORCEINLINE bool IsInteracting() const
	{
		return GetWorld()->GetTimerManager().IsTimerActive(InteractionData.InteractionCheckTimerHandle);
	}

	UPROPERTY()
	TScriptInterface<IInteractTracing> OwnerInteractTracing;

protected:
	virtual void BeginPlay() override;

	AActor* FindInteractionActorFromView();
	
	void FillInteractableData(AActor* Interactable);
	
	void FocusCurrentInteraction() const;

	void UnFocusCurrentInteraction() const;
	
	void ClearInteractableData();
	
	void StartInteracting();
	
	void EndInteracting();
	
	void HandleInteraction();
};
