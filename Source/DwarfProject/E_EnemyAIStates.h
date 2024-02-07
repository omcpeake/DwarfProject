// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "E_EnemyAIStates.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class E_EnemyAIStates : uint8
{
	Idle,
	Attacking,
	Dead
};
