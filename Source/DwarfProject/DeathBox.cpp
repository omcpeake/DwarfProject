// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathBox.h"
#include "DwarfProjectCharacter.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

ADeathBox::ADeathBox()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetBoxExtent(FVector(100, 100, 100));
	BoxComponent->SetCollisionProfileName("Trigger");
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADeathBox::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADeathBox::OnOverlapEnd);	
}


void ADeathBox::BeginPlay()
{
	Super::BeginPlay();		
	SetActorHiddenInGame(false);
}


void ADeathBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if the actor is the character class kill it
	if (OtherActor && (OtherActor != this))
	{
		ADwarfProjectCharacter* Entity = Cast<ADwarfProjectCharacter>(OtherActor);
		if (Entity)
		{
			Entity->Die();
		}
	}
}

void ADeathBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}






