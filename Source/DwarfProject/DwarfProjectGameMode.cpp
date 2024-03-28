// Copyright Epic Games, Inc. All Rights Reserved.

#include "DwarfProjectGameMode.h"
#include "DwarfProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UnmirDoor.h"

#include "Kismet/GameplayStatics.h"


ADwarfProjectGameMode::ADwarfProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ADwarfProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EnemyCount == 0)
	{
		
		

		if (DoorOpened)
			return;
					
		TSubclassOf<AUnmirDoor> classToFind;
		classToFind = AUnmirDoor::StaticClass();
		TArray<AActor*> foundEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);
		for (AActor* actor : foundEnemies)
		{
			AUnmirDoor* door = Cast<AUnmirDoor>(actor);
			if (door)
			{
				door->OpenDoor();
				DoorOpened = true;
			}
		}
	}
}

void ADwarfProjectGameMode::IncrementEnemyCount()
{
	EnemyCount++;
}

void ADwarfProjectGameMode::DecrementEnemyCount()
{
	EnemyCount--;
}
