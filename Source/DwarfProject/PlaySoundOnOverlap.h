// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaySoundOnOverlap.generated.h"

UCLASS()
class DWARFPROJECT_API APlaySoundOnOverlap : public AActor
{
	GENERATED_BODY()
	
	APlaySoundOnOverlap();

	class UBoxComponent* BoxComponent;

	//Variables
	UPROPERTY(EditAnywhere)
	USoundBase* SoundToPlay;
	//Functions
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
