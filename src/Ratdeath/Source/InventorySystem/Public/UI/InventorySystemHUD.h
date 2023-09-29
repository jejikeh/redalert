// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventorySystemHUD.generated.h"

struct FInteractableData;
DECLARE_LOG_CATEGORY_EXTERN(LogInventorySystemHUD, Log, All);

struct FInteractionData;
class UInteractionWidget;
class UMainPanelHolderWidget;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AInventorySystemHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainPanelHolderWidget> MainPanelHolderWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	
	AInventorySystemHUD();

	// NOTE(jejikeh): This may better be in another class
	// NOTE(jejikeh): This is not gonna work if we have multiple widgets of the same class
	UFUNCTION(BlueprintCallable, meta = (ToolTip="Use only on those classes that are presented in HUD. Also this does not work with multiple widgets of the same class."))
	void SetWidgetVisibility(TSubclassOf<UUserWidget> WidgetClass, ESlateVisibility Visibility) const;

	UFUNCTION(BlueprintCallable, meta = (ToolTip="Use only on those classes that are presented in HUD. Also this does not work with multiple widgets of the same class."))
	ESlateVisibility GetWidgetVisibility(TSubclassOf<UUserWidget> WidgetClass) const;
	
	UFUNCTION(BlueprintCallable)
	void UpdateInteractionWidget(const FInteractableData& InteractableData);

protected:
	UPROPERTY()
	UInteractionWidget* InteractionWidget;
	
	UPROPERTY()
	UMainPanelHolderWidget* MainPanelHolderWidget;

	virtual void BeginPlay() override;
};
