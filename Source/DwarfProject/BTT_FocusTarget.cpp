// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FocusTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AActor* PlayerActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Player.SelectedKeyName));

	if (IsValid(PlayerActor))
	{
		AIController->SetFocus(PlayerActor);

		return EBTNodeResult::Succeeded;
	}

	
	
	return EBTNodeResult::Type();
}
