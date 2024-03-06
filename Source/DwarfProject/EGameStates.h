// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "EGameStates.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameStates : uint8
{
	Menu,
	Running,
	Paused,
	Dead
};
