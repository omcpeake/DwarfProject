// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DwarfHud.generated.h"

/**
 * https://www.youtube.com/watch?v=T7v3UnL6PNU
 */
UCLASS(Abstract)
class DWARFPROJECT_API UDwarfHud : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealth(float CurrentHealth, float MaxHealth);


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HealthBar;
	

};



