// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Data/ItemDataStructs.h"
#include "Interfaces/InteractionInterface.h"
#include "RatdeathCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

public:
	FInteractionData() : Interactable(nullptr), InteractionDuration(0.0f), LastInteractionDuration(0.0f)
	{
	};

	UPROPERTY()
	AActor* Interactable;

	UPROPERTY()
	float InteractionDuration;

	UPROPERTY()
	float LastInteractionDuration;
};

UCLASS(config=Game)
class ARatdeathCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARatdeathCharacter();

#pragma region Fields

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

#pragma endregion Fields

#pragma region Functions

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	virtual void Tick(float DeltaSeconds) override;

#pragma endregion Functions

protected:
#pragma region Functions

	virtual void BeginPlay() override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void PerformInteractionCheck();
	void FoundInteractable(AActor* Interactable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

protected:
#pragma endregion Functions

#pragma region Fields
	FInteracting Interacting;

	FInteractionData InteractionData;

#pragma endregion Fields

private:
#pragma region Fields

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bHasRifle;

	float StandingEyeHeight = 55.0f;

	float CrouchEyeHeight = 25.0f;

#pragma endregion Fields
};
