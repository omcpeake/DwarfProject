// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfGameInstance.h"

EGameStates UDwarfGameInstance::GetState()
{
	return State;
}

void UDwarfGameInstance::SetState(EGameStates newState)
{
	State = newState;
}

float UDwarfGameInstance::GetSliderVolume()
{
	return SliderVolume;
}

void UDwarfGameInstance::SetSliderVolume(float newVolume)
{
	SliderVolume = newVolume;
}
