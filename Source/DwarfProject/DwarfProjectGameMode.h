// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DwarfProjectGameMode.generated.h"

UCLASS(minimalapi)
class ADwarfProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void Tick(float DeltaTime) override;

public:
	ADwarfProjectGameMode();

	int EnemyCount = 0;
	bool DoorOpened = false;

	void IncrementEnemyCount();
	void DecrementEnemyCount();
	int GetEnemyCount();

	void CheckForDoorsToOpen();
};



