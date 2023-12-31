#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

class IInteractionInterface;

UENUM()
enum class EItemRarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Legendary UMETA(DisplayName = "Legendary"),
};

UENUM()
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Misc UMETA(DisplayName = "Misc"),
	Heal UMETA(DisplayName = "Heal"),
};

USTRUCT()
struct FItemStatistics
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float DamageValue;

	UPROPERTY(EditAnywhere)
	float Price;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	FText InteractText;

	UPROPERTY(EditAnywhere)
	FText UseText;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

	// TODO: Add more data, like [Sound]
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName Id;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStatistics Statistics;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;
};
