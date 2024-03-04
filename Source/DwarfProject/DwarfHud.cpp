// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfHud.h"
#include "Components/ProgressBar.h"

void UDwarfHud::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}
