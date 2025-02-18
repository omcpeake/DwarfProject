// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"

#include "DwarfProjectCharacter.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "DwarfHud.h"
#include "Kismet/GameplayStatics.h"

AHealthPickup::AHealthPickup()
{
	

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(100, 100, 100));
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlapBegin);
	RootComponent = BoxComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	Rotation = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation"));
	Rotation->RotationRate = FRotator(0.0f, 80.0f, 0.0f);	
}

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();	
}


void AHealthPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if the actor is the character class kill it
	if (OtherActor && (OtherActor != this))
	{
		ADwarfProjectCharacter* Entity = Cast<ADwarfProjectCharacter>(OtherActor);
		if (Entity)
		{
			// if the entity is not an AI and is not at full health, heal it and destroy the pickup
			if (!Entity->GetHasAI() && Entity->GetCurrentHealth()!=Entity->GetMaxHealth())
			{
				Entity->RecieveHealth(HealingAmount);
				//update the HUD
				Entity->GetPlayerHUD()->SetHealth(Entity->GetCurrentHealth(), Entity->GetMaxHealth());
				//Play sound
				UGameplayStatics::PlaySoundAtLocation(this, HealSound, GetActorLocation());
				Destroy();
			}			
		}
	}	
}
