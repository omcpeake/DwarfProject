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

	public:
		EGameStates State;

		//only needs to be set when changing levels
		float currentHealth;
		
	
};
