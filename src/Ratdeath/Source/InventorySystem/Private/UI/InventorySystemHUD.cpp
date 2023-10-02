// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySystemHUD.h"

#include "Interfaces/InteractionInterface.h"
#include "UI/InteractionWidget.h"
#include "UI/MainPanelHolderWidget.h"

DEFINE_LOG_CATEGORY(LogInventorySystemHUD);

AInventorySystemHUD::AInventorySystemHUD()
{
}

void AInventorySystemHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!MainPanelHolderWidgetClass || !InteractionWidgetClass)
	{
		UE_LOG(LogInventorySystemHUD, Error, TEXT("MainPanelHolderWidgetClass or InteractionWidgetClass is null"));
		return;
	}
	
	MainPanelHolderWidget = CreateWidget<UMainPanelHolderWidget>(GetWorld(), MainPanelHolderWidgetClass);
	MainPanelHolderWidget->AddToViewport(5);
	MainPanelHolderWidget->SetVisibility(ESlateVisibility::Collapsed);

	InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
	InteractionWidget->AddToViewport(-1);
	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AInventorySystemHUD::SetWidgetVisibility(const TSubclassOf<UUserWidget> WidgetClass, const ESlateVisibility Visibility) const
{
	if (WidgetClass == MainPanelHolderWidgetClass && MainPanelHolderWidget)
	{
		MainPanelHolderWidget->SetVisibility(Visibility);
		return;
	}

	if (WidgetClass == InteractionWidgetClass && InteractionWidget)
	{
		InteractionWidget->SetVisibility(Visibility);
		return;
	}

	UE_LOG(LogInventorySystemHUD, Error, TEXT("WidgetClass not found"));
}

ESlateVisibility AInventorySystemHUD::GetWidgetVisibility(const TSubclassOf<UUserWidget> WidgetClass) const
{
	if (MainPanelHolderWidgetClass == WidgetClass && MainPanelHolderWidget) {
		return MainPanelHolderWidget->GetVisibility();
	}

	if (WidgetClass == InteractionWidgetClass && InteractionWidget) {
		return InteractionWidget->GetVisibility();
	}

	UE_LOG(LogInventorySystemHUD, Error, TEXT("WidgetClass not found"));
	
	return {};
}

void AInventorySystemHUD::UpdateInteractionWidget(const FInteractableData* InteractableData)
{
	if (InteractionWidget && InteractableData)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateInteractionData(InteractableData);
	}
	else
	{
		SetWidgetVisibility(InteractionWidgetClass, ESlateVisibility::Collapsed);
	}
}
