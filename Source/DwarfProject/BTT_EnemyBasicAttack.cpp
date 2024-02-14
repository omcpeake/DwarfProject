// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EnemyBasicAttack.h"
#include "DwarfProjectCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_EnemyBasicAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	ADwarfProjectCharacter* Enemy = Cast<ADwarfProjectCharacter>(AIController->GetPawn());

	if (IsValid(Enemy))
	{
		Enemy->MakeAttack(true); // true for randomly selected attack anim
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Type();
}
