// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteractionWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"
#include "Internationalization/Internationalization.h"


void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ActionText->SetText(FText::FromString("Press"));
	CurrentInteractionDuration = 0.0f;
}

void UInteractionWidget::UpdateInteractionData(const FInteractableData& InteractableData) const
{
	switch (InteractableData.InteractableType)
	{
	case EInteractableType::Pickup:
		ActionText->SetText(FText::FromString("Press"));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		if (InteractableData.Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			QuantityText->SetText(FText::Format(FText::FromString("x{0}"), InteractableData.Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}

		break;
	case EInteractableType::Interact:
		break;
	case EInteractableType::Switch:
		break;
	case EInteractableType::Container:
		break;
	default: ;
	}
}

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.0f;
}
