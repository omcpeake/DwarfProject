// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "DwarfGameInstance.h"

void UMainMenu::NativeConstruct()
{
	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenu::StartGameButtonOnClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonOnClicked);
	}
}

void UMainMenu::StartGameButtonOnClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
	UDwarfGameInstance* GameInstance = Cast<UDwarfGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		GameInstance->State = EGameStates::Running;
	}
}

void UMainMenu::QuitButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
