// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameEndBox.generated.h"

UCLASS()
class DWARFPROJECT_API AGameEndBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameEndBox();

private:
	class UBoxComponent* BoxComponent;
	

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UDeathScreen> GameEndScreenClass;

	UPROPERTY()
	class UDeathScreen* GameEndScreen;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
