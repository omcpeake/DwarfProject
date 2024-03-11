// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DwarfGameInstance.h"

#include "DeathScreen.generated.h"

/**
 * 
 */
UCLASS()
class DWARFPROJECT_API UDeathScreen : public UUserWidget
{
	GENERATED_BODY()
	

public:
	//Buttons
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ReturnToMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

	virtual void NativeConstruct() override;

	UDwarfGameInstance* GameInstance;

	UFUNCTION()
	void RestartButtonOnClicked();
	UFUNCTION()
	void ReturnToMenuButtonOnClicked();
	//TODO option menu
	UFUNCTION()
	void QuitButtonOnClicked();
};
