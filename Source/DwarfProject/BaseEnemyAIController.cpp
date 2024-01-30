// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "DwarfProjectCharacter.h"

void ABaseEnemyAIController::BeginPlay()
{
	ADwarfProjectCharacter* Enemy = Cast<ADwarfProjectCharacter>(GetPawn());
	
	if (IsValid(Enemy))
	{
		RunBehaviorTree(Enemy->GetBehaviourTree());
	}
}
