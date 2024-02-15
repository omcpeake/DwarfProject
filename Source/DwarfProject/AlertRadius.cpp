// Fill out your copyright notice in the Description page of Project Settings.


#include "AlertRadius.h"
#include "Components/SphereComponent.h"
#include "BaseEnemyAIController.h"
#include "DwarfProjectCharacter.h"



AAlertRadius::AAlertRadius()
{
	AlertSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AlertSphere"));
	AlertSphere->SetupAttachment(RootComponent);
	AlertSphere->SetSphereRadius(800.0f);
	AlertSphere->SetCollisionProfileName("Trigger");
	AlertSphere->OnComponentBeginOverlap.AddDynamic(this, &AAlertRadius::OnOverlapBegin);
	AlertSphere->OnComponentEndOverlap.AddDynamic(this, &AAlertRadius::OnOverlapEnd);
}




void AAlertRadius::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	
}

void AAlertRadius::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AAlertRadius::UpdateStatesToAttacking()
{		
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ADwarfProjectCharacter::StaticClass());
	for (auto& Actor : OverlappingActors)
	{		
		ADwarfProjectCharacter* Unit = Cast<ADwarfProjectCharacter>(Actor);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Here"));
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
	
}




