// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEndBox.h"
#include "Components/BoxComponent.h"
#include "DwarfGameInstance.h"
#include "DeathScreen.h"
#include "DwarfProjectCharacter.h"


// Sets default values
AGameEndBox::AGameEndBox()
{

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetBoxExtent(FVector(100, 100, 100));
	BoxComponent->SetCollisionProfileName("Trigger");
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGameEndBox::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AGameEndBox::OnOverlapEnd);

}

void AGameEndBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADwarfProjectCharacter* Player = Cast<ADwarfProjectCharacter>(OtherActor);
	if (Player->GetHasAI() == false)
	{
		UDwarfGameInstance* GameInstance = Cast<UDwarfGameInstance>(GetGameInstance());
		APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController((GetWorld())));
		MyPlayer->SetPause(true);
		MyPlayer->bShowMouseCursor = true;

		GameEndScreen = CreateWidget<UDeathScreen>(GetWorld(), GameEndScreenClass);
		GameEndScreen->AddToViewport();
	}	
}

void AGameEndBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



