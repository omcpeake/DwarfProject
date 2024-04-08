// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndScreen.generated.h"

/**
 * 
 */
UCLASS()
class DWARFPROJECT_API UGameEndScreen : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitToMenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;


	virtual void NativeConstruct() override;

	UFUNCTION()
	void QuitToMenuOnClicked();
	UFUNCTION()
	void QuitButtonOnClicked();
	
};
