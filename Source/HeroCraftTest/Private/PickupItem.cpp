// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include "Components/BoxComponent.h"
#include "InventoryGameState.h"
#include "PickupItemPlayerController.h"
#include "HeroCraftTest/HeroCraftTestCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemType = EItemType::EIT_Bottle;
	DataTablePath = "/Game/ThirdPersonCPP/Blueprints/DT_InventoryItemsDB.DT_InventoryItemsDB";

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	BoxComponent->SetBoxExtent(FVector(40.f, 40.f, 40.f));
	BoxComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	BoxComponent->SetGenerateOverlapEvents(true);
	RootComponent = BoxComponent;

	// Definition for the Mesh that will serve as our visual representation.
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &APickupItem::ActorBeginOverlap);

	Initialize(ItemType);
}

void APickupItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(APickupItem, ItemType))
	{
		Initialize(ItemType);
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void APickupItem::Initialize(EItemType InItemType)
{
	ItemType = InItemType;

	UDataTable* ItemTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *DataTablePath));
	if (!ItemTable)
		return;

	TArray<FName> RowNames = ItemTable->GetRowNames();

	const FString ContextString(TEXT("GENERAL"));

	for (auto RowName : RowNames)
	{
		FInventoryItem* Item = ItemTable->FindRow<FInventoryItem>(RowName, ContextString);
		if (Item->ItemType == ItemType)
		{
			SetupItemFromInventory(*Item);
			break;
		}
	}
}

void APickupItem::SetupItemFromInventory(FInventoryItem Item)
{
	Name = Item.Name;
	Description = Item.Description;
	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *Item.StaticMeshAssetPath));
	StaticMesh->SetStaticMesh(Mesh);
}

void APickupItem::ActorBeginOverlap(AActor* Self, AActor* OtherActor)
{
	AHeroCraftTestCharacter* Character = Cast<AHeroCraftTestCharacter>(OtherActor);
	if (!Character)
		return;

	if (auto APIController = Cast<APickupItemPlayerController>(Character->GetController()))
	{
		if (APIController->AddItemToInventory(this))
		{
			Character->SetStaticMesh(StaticMesh->GetStaticMesh());
			Destroy();
		}	
	}
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
