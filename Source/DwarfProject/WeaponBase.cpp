// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Root component
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
	SetActorEnableCollision(false);
		

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::UpdateWeaponMesh(UStaticMesh* NewMesh)
{
	WeaponMesh->SetStaticMesh(NewMesh);
}

