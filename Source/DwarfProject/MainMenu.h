// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class DWARFPROJECT_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* StartGameButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreditsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartGameButtonOnClicked();
	UFUNCTION()
	void CreditsButtonOnClicked();
	UFUNCTION()
	void QuitButtonOnClicked();


};
