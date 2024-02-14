// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "E_EnemyAIStates.h"
#include "Components/SphereComponent.h"
#include "DwarfProjectCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AlertRadius.h"




ABaseEnemyAIController::ABaseEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerception();
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedPawn = Cast<ADwarfProjectCharacter>(InPawn);
	if (IsValid(PossessedPawn))
	{
		RunBehaviorTree(PossessedPawn->GetBehaviourTree());

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

void ABaseEnemyAIController::SetStateAsDead()
{
	GetBlackboardComponent()->SetValueAsEnum("States", (uint8)E_EnemyAIStates::Dead);
}

uint8 ABaseEnemyAIController::GetStateAsInt8()
{
	
	return GetBlackboardComponent()->GetValueAsEnum("States");
}

void ABaseEnemyAIController::SetTarget(AActor* Target)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ABaseEnemyAIController::TargetPlayer()
{
	GetBlackboardComponent()->SetValueAsObject("Target", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ABaseEnemyAIController::SetupPerception()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 1200.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 400.0f;
		SightConfig->PeripheralVisionAngleDegrees = 60.0f;
		SightConfig->SetMaxAge(4.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 150.0f;
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 150.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		///
		/// Put damage config here if we want to use it
		///


		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyAIController::OnTargetPerceptionUpdated);

		// will add forgotten if I ever manage to find a single person who has this line of code working
		//GetPerceptionComponent()->OnTargetPerceptionForgotten.AddDynamic(this, &ABaseEnemyAIController::OnTargetPerceptionForgotten);

		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}

}


void ABaseEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (ADwarfProjectCharacter* Target = Cast<ADwarfProjectCharacter>(Actor))
	{
		//assuming that the player is the only non hostile actor and that there is no friendly npcs
		if (Target->GetIsHostile() == false)
		{			
			PossessedPawn->GetAlertRadius()->UpdateStatesToAttacking();					
		}		
	}	
}





