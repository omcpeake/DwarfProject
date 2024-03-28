// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "Components/TimelineComponent.h"

#include "UnmirDoor.generated.h"

//https://www.youtube.com/watch?v=1y-FnncH-XQ
class UCurveFloat;

UCLASS()
class DWARFPROJECT_API AUnmirDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnmirDoor();

	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FTimeline CurveTimeline;
	UPROPERTY(EditAnywhere, Category = "DoorProperties")
	UCurveFloat* CurveFloat;


	//UPROPERTY(EditAnywhere, Category = "DoorProperties")
	FVector CloseLocation;
	//UPROPERTY(EditAnywhere, Category = "DoorProperties")
	FVector OpenLocation;

	UPROPERTY(EditAnywhere, Category = "DoorProperties")
	float ZOffset;


	
	

public:	
	void OpenDoor();

};
