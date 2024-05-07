// Fill out your copyright notice in the Description page of Project Settings.


#include "UnmirDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AUnmirDoor::AUnmirDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

void AUnmirDoor::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));

		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(false);

		CloseLocation = OpenLocation = GetActorLocation();
		OpenLocation.Z += ZOffset;
		
	}
	
}

void AUnmirDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}

void AUnmirDoor::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(CloseLocation, OpenLocation, Value);
	//NewLocation.Z += ZOffset;
	SetActorLocation(NewLocation);

}

void AUnmirDoor::OpenDoor()
{
	if (GetLevel()->GetName() != "MainMenu") //I dont know if this line of code actually does anything
	{
		CurveTimeline.PlayFromStart();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OpenSound, GetActorLocation());
	}
	
}