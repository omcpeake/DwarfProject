// Fill out your copyright notice in the Description page of Project Settings.


#include "AlertRadius.h"
#include "Components/SphereComponent.h"
#include "BaseEnemyAIController.h"
#include "DwarfProjectCharacter.h"



AAlertRadius::AAlertRadius()
{
	AlertSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AlertSphere"));
	AlertSphere->SetupAttachment(RootComponent);
	AlertSphere->SetSphereRadius(1200.0f);
	AlertSphere->SetCollisionProfileName("Trigger");
	AlertSphere->OnComponentBeginOverlap.AddDynamic(this, &AAlertRadius::OnOverlapBegin);
	AlertSphere->OnComponentEndOverlap.AddDynamic(this, &AAlertRadius::OnOverlapEnd);
}

void AAlertRadius::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ADwarfProjectCharacter::StaticClass());

	for (auto& Unit : OverlappingActors)
	{
		if (ADwarfProjectCharacter* Target = Cast<ADwarfProjectCharacter>(Unit))
		{
			if (Target->GetHasAI())
			{
				UnitsInAlertRange.Add(Target);
			}
		}

	}
}


void AAlertRadius::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (ADwarfProjectCharacter* Target = Cast<ADwarfProjectCharacter>(OtherActor))
	{
		if (Target->GetHasAI())
		{
			UnitsInAlertRange.Add(Target);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Added")));
			
		}
	}
	
}

void AAlertRadius::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ADwarfProjectCharacter* Target = Cast<ADwarfProjectCharacter>(OtherActor))
	{					
		UnitsInAlertRange.Remove(Target);	
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Removed a mf")));
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("End Overlap")));
}

void AAlertRadius::UpdateStatesToAttacking()
{
	
	
	for (auto& Unit : UnitsInAlertRange)
	{		
		AController* myController = Unit->GetController();
		ABaseEnemyAIController* myBaseEnemyAIController = Cast<ABaseEnemyAIController>(myController);
		if (myBaseEnemyAIController)
		{
			myBaseEnemyAIController->TargetPlayer();
			if (myBaseEnemyAIController->GetStateAsInt8() == (uint8)E_EnemyAIStates::Idle)
			{
				//only start attacking from idle
				myBaseEnemyAIController->SetStateAsAttacking();

			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast Failed"));
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Here"));
}

TArray<ADwarfProjectCharacter*> AAlertRadius::GetUnitsInAlertRange()
{
	return UnitsInAlertRange;
}



