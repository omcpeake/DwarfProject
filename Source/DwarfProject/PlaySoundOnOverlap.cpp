// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySoundOnOverlap.h"
#include "DwarfProjectCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlaySoundOnOverlap::APlaySoundOnOverlap()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(400, 100, 400));
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetupAttachment(RootComponent);
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlaySoundOnOverlap::OnOverlapBegin);
}

void APlaySoundOnOverlap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADwarfProjectCharacter* Character = Cast<ADwarfProjectCharacter>(OtherActor);
	//check if this is the player
	if (Character && !Character->GetHasAI())
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());
		Destroy();
	}
}


