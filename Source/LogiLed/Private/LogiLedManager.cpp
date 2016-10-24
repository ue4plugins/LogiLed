// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "LogiLedPCH.h"
#include "LogiLedManager.h"


/* FLogiLedManager structors
 *****************************************************************************/

FLogiLedManager::FLogiLedManager()
{
}


/* FLogiLedManager interface
 *****************************************************************************/

void FLogiLedManager::PlayAnimation(UCurveLinearColor* ColorCurve)
{
	Animation.Curve = ColorCurve;
	Animation.Time = 0.0f;
}


void FLogiLedManager::PlayAnimation(LogiLed::KeyName KeyName, UCurveLinearColor* ColorCurve)
{
	FAnimation& KeyAnimation = KeyAnimations.FindOrAdd(KeyName);
	{
		KeyAnimation.Curve = ColorCurve;
		KeyAnimation.Time = 0.0f;
	}
}


void FLogiLedManager::StopAnimations()
{
	Animation.Curve.Reset();
	KeyAnimations.Empty();
}


void FLogiLedManager::StopAnimations(LogiLed::KeyName KeyName)
{
	KeyAnimations.Remove(KeyName);
}


/* FTickableGameObject interface
 *****************************************************************************/

TStatId FLogiLedManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FLogiLedManager, STATGROUP_Tickables);
}


bool FLogiLedManager::IsTickable() const
{
	return (Animation.Curve != nullptr) || (KeyAnimations.Num() > 0);
}


void FLogiLedManager::Tick(float DeltaTime)
{
	// global animation
	if (Animation.Curve != nullptr)
	{
		const FColor RgbColor = Animation.Curve->GetLinearColorValue(Animation.Time).ToFColor(false);
		::LogiLedSetLighting(RgbColor.R, RgbColor.G, RgbColor.B);

		Animation.Time += DeltaTime;
	}

	// override individual keys
	for (auto KeyAnimationsPair : KeyAnimations)
	{
		FAnimation& KeyAnimation = KeyAnimationsPair.Value;

		if (KeyAnimation.Curve != nullptr)
		{
			const FColor RgbColor = Animation.Curve->GetLinearColorValue(Animation.Time).ToFColor(false);
			::LogiLedSetLightingForKeyWithKeyName(KeyAnimationsPair.Key, RgbColor.R, RgbColor.G, RgbColor.B);

			KeyAnimation.Time += DeltaTime;
		}
	}
}
