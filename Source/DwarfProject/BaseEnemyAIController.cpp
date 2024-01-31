// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "DwarfProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ABaseEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	ADwarfProjectCharacter* Enemy = Cast<ADwarfProjectCharacter>(GetPawn());	
	if (IsValid(Enemy))
	{
		RunBehaviorTree(Enemy->GetBehaviourTree());
		//GetBlackboardComponent()->SetValueAsObject("Player", GetWorld()->GetFirstPlayerController()->GetPawn());
		GetBlackboardComponent()->SetValueAsObject("Player", UGameplayStatics::GetPlayerCharacter(this , 0));
	}
}
