// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupItemPlayerController.h"
#include "HeroCraftTest/HeroCraftTestCharacter.h"
#include "PickupItem.h"

bool APickupItemPlayerController::AddItemToInventory(APickupItem* Item)
{
	if (bHasItem)
		return false;

	FInventoryItem InventoryItem;
	InventoryItem.ItemType = Item->ItemType;
	InventoryItem.Name = Item->Name;
	InventoryItem.Description = Item->Description;

	Inventory = InventoryItem;
	bHasItem = true;
	InventoryChangedDelegate.Broadcast();

	return true;
}

void APickupItemPlayerController::RemoveItemFromInventory()
{
	if (!bHasItem)
		return;

	bHasItem = false;
	InventoryChangedDelegate.Broadcast();

	AHeroCraftTestCharacter* HCTCharacter = Cast<AHeroCraftTestCharacter>(GetPawn());
	
	if (!HCTCharacter)
	{
		FString Message = FString(TEXT("Cast to AHeroCraftCharacter failed"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Message);
		return;
	}

	FVector NewLocation = FVector(HCTCharacter->GetActorLocation() + FVector(200.f * HCTCharacter->GetActorForwardVector()));
	FVector Location = (HCTCharacter) ? NewLocation : FVector(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	APickupItem* SpawnedItem = GetWorld()->SpawnActor<APickupItem>(Location, Rotation);
	if (SpawnedItem)
	{
		SpawnedItem->Initialize(Inventory.ItemType);
	}	
}
