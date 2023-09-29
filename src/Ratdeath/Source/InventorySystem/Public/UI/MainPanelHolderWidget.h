// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPanelHolderWidget.generated.h"

class UInteractComponent;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UMainPanelHolderWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// NOTE(jejikeh): This will moved
	// NOTE(jejikeh): Maybe create separate component for `CONTAINER` logic
	UPROPERTY()
	APawn* OwningPawn;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
