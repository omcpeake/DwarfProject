// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathScreen.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DwarfProjectCharacter.h"

void UDeathScreen::NativeConstruct()
{
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UDeathScreen::RestartButtonOnClicked);
	}
	if (ReturnToMenuButton)
	{
		ReturnToMenuButton->OnClicked.AddDynamic(this, &UDeathScreen::ReturnToMenuButtonOnClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UDeathScreen::QuitButtonOnClicked);
	}

	GameInstance = Cast<UDwarfGameInstance>(GetWorld()->GetGameInstance());
}

void UDeathScreen::RestartButtonOnClicked()
{
	//Reload level 1
	GameInstance->SetState(EGameStates::Running);	
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
	//RemoveFromViewport();

}

void UDeathScreen::ReturnToMenuButtonOnClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	GameInstance->SetState(EGameStates::Menu);
}

void UDeathScreen::QuitButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);

}