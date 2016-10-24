// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Tickable.h"


/**
 * Manages Logitech LED state and timing.
 */
class FLogiLedManager
	: public FTickableGameObject
{
	struct FAnimation
	{
		TWeakObjectPtr<UCurveLinearColor> Curve;
		float Time;
	};

public:

	/** Default constructor. */
	FLogiLedManager();

public:

	void PlayAnimation(UCurveLinearColor* ColorCurve);

	void PlayAnimation(LogiLed::KeyName KeyName, UCurveLinearColor* ColorCurve);

	void StopAnimations();

	void StopAnimations(LogiLed::KeyName KeyName);

public:

	//~ FTickableGameObject interface

	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;

private:

	/** Color animation for all keys. */
	FAnimation Animation;

	/** Color animation for specific keys. */
	TMap<LogiLed::KeyName, FAnimation> KeyAnimations;
};
