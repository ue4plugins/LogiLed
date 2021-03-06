// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LogiLedManager.h"

#include "Classes/Curves/CurveLinearColor.h"

#if WITH_EDITOR
	#include "Editor.h"
#endif


/* FLogiLedManager structors
 *****************************************************************************/

FLogiLedManager::FLogiLedManager()
{
#if WITH_EDITOR
	FEditorDelegates::EndPIE.AddRaw(this, &FLogiLedManager::HandleEditorEndPIE);
#endif
}


FLogiLedManager::~FLogiLedManager()
{
#if WITH_EDITOR
	FEditorDelegates::EndPIE.RemoveAll(this);
#endif
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
		const FLinearColor Percentage = Animation.Curve->GetLinearColorValue(Animation.Time).GetClamped() * 100.0f;
		::LogiLedSetLighting(Percentage.R, Percentage.G, Percentage.B);

		Animation.Time += DeltaTime;
	}

	// override individual keys
	for (auto& KeyAnimationsPair : KeyAnimations)
	{
		FAnimation& KeyAnimation = KeyAnimationsPair.Value;

		if (KeyAnimation.Curve != nullptr)
		{
			const FLinearColor Percentage = KeyAnimation.Curve->GetLinearColorValue(KeyAnimation.Time).GetClamped() * 100.0f;
			::LogiLedSetLightingForKeyWithKeyName(KeyAnimationsPair.Key, Percentage.R, Percentage.G, Percentage.B);

			KeyAnimation.Time += DeltaTime;
		}
	}
}


/* FLogiLedManager callbacks
 *****************************************************************************/

#if WITH_EDITOR

void FLogiLedManager::HandleEditorEndPIE(bool bIsSimulating)
{
	StopAnimations();
	::LogiLedStopEffects();
}

#endif
