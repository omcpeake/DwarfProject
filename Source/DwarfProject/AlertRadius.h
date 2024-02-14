// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "E_EnemyAIStates.h"


#include "AlertRadius.generated.h"

class ADwarfProjectCharacter;

UCLASS()
class DWARFPROJECT_API AAlertRadius : public ATriggerSphere
{
	GENERATED_BODY()
	
	AAlertRadius();

	virtual void BeginPlay() override;

	class USphereComponent* AlertSphere;

	TArray<ADwarfProjectCharacter*> UnitsInAlertRange;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	
	void UpdateStatesToAttacking();

	TArray<ADwarfProjectCharacter*> GetUnitsInAlertRange();
};
