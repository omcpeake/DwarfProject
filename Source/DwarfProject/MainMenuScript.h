// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuScript.generated.h"

/**
 * 
 */
UCLASS()
class DWARFPROJECT_API AMainMenuScript : public ALevelScriptActor
{
	GENERATED_BODY()
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UMainMenu> MainMenuClass;
	UPROPERTY()
	class UMainMenu* MainMenu;

	UFUNCTION(BlueprintCallable)
	void EnableMenu(TSubclassOf<class UMainMenu> MenuClass);

};
