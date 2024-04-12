// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EGameStates.h"
#include "DwarfGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DWARFPROJECT_API UDwarfGameInstance : public UGameInstance
{
	GENERATED_BODY()


private:
	EGameStates State;

	//only needs to be set when changing levels
	float currentHealth;

	float SliderVolume = 1;


public:
	float testval = 1;

		UFUNCTION(BlueprintCallable, Category = "Game State")
		EGameStates GetState();
		UFUNCTION(BlueprintCallable, Category = "Game State")
		void SetState(EGameStates newState);

		
		UFUNCTION(BlueprintCallable, Category = "Slider Volume")
		float GetSliderVolume();
		UFUNCTION(BlueprintCallable, Category = "Slider Volume")
		void SetSliderVolume(float newVolume);
	
};
