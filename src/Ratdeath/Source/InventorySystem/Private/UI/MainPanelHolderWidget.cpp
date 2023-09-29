// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainPanelHolderWidget.h"

void UMainPanelHolderWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMainPanelHolderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto Pawn = GetOwningPlayerPawn())
	{
		OwningPawn = Pawn;
	}
}

bool UMainPanelHolderWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
