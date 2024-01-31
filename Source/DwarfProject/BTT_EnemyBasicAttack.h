// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_EnemyBasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class DWARFPROJECT_API UBTT_EnemyBasicAttack : public UBTTaskNode
{
	GENERATED_BODY()

	//may or may not need ovveride
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
