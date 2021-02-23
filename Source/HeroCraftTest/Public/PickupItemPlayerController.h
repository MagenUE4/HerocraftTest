// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerController.h"
#include "PickupItemPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryChangedDelegate);

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Bottle	UMETA(DisplayName = "Bottle"),
	EIT_Stone	UMETA(DisplayName = "Stone"),
	EIT_Food	UMETA(DisplayName = "Food")
};

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
	FString StaticMeshAssetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItem")
	FText Description;
};

/**
 * 
 */
UCLASS()
class HEROCRAFTTEST_API APickupItemPlayerController : public APlayerController
{
	GENERATED_BODY()

	bool bHasItem;

public:

	UFUNCTION()
	bool AddItemToInventory(class APickupItem* Item);

	UFUNCTION()
	void RemoveItemFromInventory();

	/** Delegate to tell when inventory content changed. */
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FInventoryChangedDelegate InventoryChangedDelegate;

	UFUNCTION()
	FORCEINLINE FInventoryItem GetInventory() const { return Inventory; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool HasItem() const { return bHasItem; }

protected:

	/** Inventory is only for one item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	FInventoryItem Inventory;
};
