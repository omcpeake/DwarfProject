// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DwarfGameInstance.h"

#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DWARFPROJECT_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	//Buttons
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ReturnToMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

	virtual void NativeConstruct() override;

	UDwarfGameInstance *GameInstance;

	UFUNCTION()
	void ResumeButtonOnClicked();
	UFUNCTION()
	void ReturnToMenuButtonOnClicked();
	//TODO option menu
	UFUNCTION()
	void QuitButtonOnClicked();

};
