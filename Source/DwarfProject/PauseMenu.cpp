// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DwarfProjectCharacter.h"


void UPauseMenu::NativeConstruct()
{
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeButtonOnClicked);
	}
	if (ReturnToMenuButton)
	{
		ReturnToMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::ReturnToMenuButtonOnClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitButtonOnClicked);
	}

	GameInstance = Cast<UDwarfGameInstance>(GetWorld()->GetGameInstance());
}

void UPauseMenu::ResumeButtonOnClicked()
{
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	GameInstance->SetState(EGameStates::Running);
	
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController((GetWorld())));
	MyPlayer->SetPause(false);
	MyPlayer->bShowMouseCursor = false;
	RemoveFromViewport();

}

void UPauseMenu::ReturnToMenuButtonOnClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	GameInstance->SetState(EGameStates::Menu);
}

void UPauseMenu::QuitButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	
}
