// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseEnemyAIController.generated.h"


/**
 * 
 */


UCLASS()
class DWARFPROJECT_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit ABaseEnemyAIController(FObjectInitializer const& ObjectInitializer);

	void SetStateAsAttacking();
	void SetStateAsIdle();
	void SetStateAsDead();

	uint8 GetStateAsInt8();

	void SetTarget(AActor* Target);

	void TargetPlayer();	

private:
	//https://sologamedevblog.com/tutorials/unreal-perception-c-friend-or-enemy/ not using this but could be useful

	//https://www.youtube.com/watch?v=c3DxMukF8UI
	void SetupPerception();

	class UAISenseConfig_Sight* SightConfig;

	//Reference to the possessed pawn
	class ADwarfProjectCharacter* PossessedPawn;

	//class UAISenseConfig_Damage* DamageConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	//UFUNCTION()
	//void OnTargetPerceptionForgotten(AActor* Actor, FAIStimulus Stimulus);
	
	protected:
		virtual void OnPossess(APawn* InPawn) override;	
};
