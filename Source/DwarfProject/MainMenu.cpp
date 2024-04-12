// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "DwarfGameInstance.h"

void UMainMenu::NativeConstruct()
{
	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenu::StartGameButtonOnClicked);
	}
	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::CreditsButtonOnClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitButtonOnClicked);
	}
}

void UMainMenu::StartGameButtonOnClicked()
{
	RemoveFromViewport();	
	UDwarfGameInstance* GameInstance = Cast<UDwarfGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->SetState(EGameStates::Running);		
	}
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");	
}

void UMainMenu::CreditsButtonOnClicked()
{

}

void UMainMenu::QuitButtonOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
