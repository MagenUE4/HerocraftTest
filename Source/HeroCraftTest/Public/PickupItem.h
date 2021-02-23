// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupItemPlayerController.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class HEROCRAFTTEST_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

	/** Collision component for item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComponent;

	/** Visual representation of item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parameters")
	FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parameters")
	FText Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parameters")
	FString DataTablePath;

	UFUNCTION()
	void Initialize(EItemType InItemType);

	UFUNCTION()
	void SetupItemFromInventory(FInventoryItem Item);

	/** Represents item's begavior when its collision box is overlapped */
	UFUNCTION()
	void ActorBeginOverlap(class AActor* Self, class AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
