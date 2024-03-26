// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCamShake.h"

UMyCamShake::UMyCamShake()
{
	OscillationDuration = 0.15f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;
	RotOscillation.Pitch.Amplitude = FMath::RandRange(1.0f, 2.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(10.0f, 20.0f);
	RotOscillation.Yaw.Amplitude = FMath::RandRange(1.0f, 2.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(10.0f, 20.0f);
}
