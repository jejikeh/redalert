// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "Interfaces/InteractTracing.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InteractComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInteractComponent, Log, All);

class UInteractionWidget;
class AInventorySystemHUD;
class IInteractionInterface;

USTRUCT(BlueprintType)
struct FInteractionData
{
	GENERATED_BODY()

	UPROPERTY()
	UActorComponent* Interactable;

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

	void SetInteractionObject(UActorComponent* InteractableComponent)
	{
		Interactable = InteractableComponent;
		if (UKismetSystemLibrary::DoesImplementInterface(InteractableComponent, UInteractionInterface::StaticClass()))
		{
			InteractionObject = InteractableComponent;
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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	void StartInteracting();

	void EndInteracting();

protected:
	virtual void BeginPlay() override;

	UActorComponent* FindInteractionActorWithInteractionComponentFromView();
	
	void FillInteractableData(UActorComponent* Interactable);
	
	void FocusCurrentInteraction() const;

	void UnFocusCurrentInteraction() const;
	
	void ClearInteractableData();
	
	void HandleInteraction();

	UPROPERTY()
	AInventorySystemHUD* InventorySystemHUD;
};
