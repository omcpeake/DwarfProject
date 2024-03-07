// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuScript.h"
#include "MainMenu.h"
#include "Blueprint/UserWidget.h"

void AMainMenuScript::BeginPlay()
{
	Super::BeginPlay();
	//EnableMenu(MainMenuClass);
	

}

void AMainMenuScript::EnableMenu(TSubclassOf<class UMainMenu> MenuClass)
{
	if (MainMenuClass)
	{
		MainMenu = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
			APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController((GetWorld())));
			if (MyPlayer)
			{
				MyPlayer->SetPause(true);
				MyPlayer->bShowMouseCursor = true;
			}
		}
	}
}
