// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

struct FInteractableData;
class UProgressBar;
class UTextBlock;
struct FInteractionData;
class UInteractComponent;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Inventory System")
	UInteractComponent* OwnerPlayerInteractComponent;

	void UpdateInteractionData(const FInteractableData* InteractableData) const;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory System | Interaction Data")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory System | Interaction Data")
	UTextBlock* DescriptionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory System | Interaction Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory System | Interaction Data")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory System | Interaction Data")
	UProgressBar* InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Inventory System | Interaction Data")
	float CurrentInteractionDuration;

	UFUNCTION(BlueprintCallable, Category = "Inventory System | Interaction Data")
	float UpdateInteractionProgress();
	
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
};
