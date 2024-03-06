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

void UDwarfHud::DarkenParryIcon()
{
	if (ParryIcon)
	{
		ParryIcon->SetColorAndOpacity(FLinearColor(0.1f, 0.1f, 0.1f, 1.0f));
	}
}

void UDwarfHud::BrightenParryIcon()
{
	if (ParryIcon)
	{
		ParryIcon->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}


