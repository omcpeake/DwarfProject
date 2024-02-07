// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyAIController.h"
#include "DwarfProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "E_EnemyAIStates.h"




ABaseEnemyAIController::ABaseEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerception();
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ADwarfProjectCharacter* Enemy = Cast<ADwarfProjectCharacter>(InPawn);
	if (IsValid(Enemy))
	{
		RunBehaviorTree(Enemy->GetBehaviourTree());

		//GetBlackboardComponent()->SetValueAsObject("Target", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		SetStateAsIdle();		
		
	}
}

void ABaseEnemyAIController::SetStateAsAttacking()
{
	//TODO - if we have more targets for enemies to attack set the target here
	GetBlackboardComponent()->SetValueAsEnum("States", (uint8)E_EnemyAIStates::Attacking);
}

void ABaseEnemyAIController::SetStateAsIdle()
{
	GetBlackboardComponent()->SetValueAsEnum("States", (uint8)E_EnemyAIStates::Idle);
}


void ABaseEnemyAIController::SetupPerception()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 800.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 200.0f;
		SightConfig->PeripheralVisionAngleDegrees = 60.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 200.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;


		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyAIController::OnTargetPerceptionUpdated);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}

}

void ABaseEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// this will just set the target to the player if it sees literally anything
	GetBlackboardComponent()->SetValueAsObject("Target", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetStateAsAttacking();

}


