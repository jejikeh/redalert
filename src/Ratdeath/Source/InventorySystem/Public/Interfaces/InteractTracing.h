// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractTracing.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractTracing : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYSYSTEM_API IInteractTracing
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interacting System | Events")
	FVector GetTraceStartVector();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interacting System | Events")
	FRotator GetTraceRotation();
};
