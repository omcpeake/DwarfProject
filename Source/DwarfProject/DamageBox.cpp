// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageBox.h"
#include "DwarfProjectCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ADamageBox::ADamageBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(400, 100, 400));
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetupAttachment(RootComponent);
	RootComponent = BoxComponent;

}

// Called when the game starts or when spawned
void ADamageBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ADwarfProjectCharacter::StaticClass());
	for (auto& Actor : OverlappingActors)
	{
		ADwarfProjectCharacter* Unit = Cast<ADwarfProjectCharacter>(Actor);
		if (Unit)
		{
			Unit->RecieveDamage(10.0f);
		}
	}

}

