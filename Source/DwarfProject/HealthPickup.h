// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class DWARFPROJECT_API AHealthPickup : public AActor
{
	GENERATED_BODY()
	AHealthPickup();

	virtual void BeginPlay() override;


	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "HealthPickupSetup")
	UStaticMeshComponent* MeshComponent;

	URotatingMovementComponent* Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthPickupSetup", meta = (AllowPrivateAccess = "true"))
	float HealingAmount;


	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

};
