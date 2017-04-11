// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Containers/Map.h"
#include "Templates/SharedPointer.h"
#include "Tickable.h"
#include "UObject/WeakObjectPtr.h"

#include "LogitechLEDLib.h"

class UCurveLinearColor;


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

	/** Virtual destructor. */
	~FLogiLedManager();

public:

	/**
	 * Play a color curve animation on all keys.
	 *
	 * @param ColorCurve The color curve.
	 * @see StopAnimations
	 */
	void PlayAnimation(UCurveLinearColor* ColorCurve);

	/**
	 * Play a color curve animation on the specified key.
	 *
	 * @param KeyName The key to play the animation on.
	 * @param ColorCurve The color curve.
	 * @see StopAnimations
	 */
	void PlayAnimation(LogiLed::KeyName KeyName, UCurveLinearColor* ColorCurve);

	/**
	 * Stop color curve animations on all keys.
	 *
	 * @see PlayAnimation
	 */
	void StopAnimations();

	/**
	 * Stop color curve animation on the specified key.
	 *
	 * @param KeyName The name of the key to stop the animation on.
	 * @see PlayAnimation
	 */
	void StopAnimations(LogiLed::KeyName KeyName);

public:

	//~ FTickableGameObject interface

	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR

private:

	/** Callback for when PIE or SIE ends. */
	void HandleEditorEndPIE(bool bIsSimulating);

#endif

private:

	/** Color animation for all keys. */
	FAnimation Animation;

	/** Color animation for specific keys. */
	TMap<LogiLed::KeyName, FAnimation> KeyAnimations;
};
