// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfHud.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UDwarfHud::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UDwarfHud::DarkenShieldIcon()
{
	if (Shield)
	{
		Shield->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
	}
}

void UDwarfHud::BrightenShieldIcon()
{
	if (Shield)
	{
		Shield->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}


