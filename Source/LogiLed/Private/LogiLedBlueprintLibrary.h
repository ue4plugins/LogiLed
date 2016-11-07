// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogiLedManager.h"
#include "LogiLedBlueprintLibrary.generated.h"


class UCurveLinearColor;
class UTexture;



/**
 * Enumerates available Logitech LED device types.
 */
UENUM()
enum class ELogiLedDeviceType : uint8
{
	All,
	Monochrome,
	PerKeyRgb,
	Rgb
};


/**
 * Enumerates available Logitech LED mouse and keyboard keys.
 */
UENUM()
enum class ELogiLedKeys : uint8
{
	Escape,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	PrintScreen,
	ScrollLock,
	PauseBreak,
	Tilde,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Zero,
	Minus,
	Equals,
	Backspace,
	Insert,
	Home,
	PageUp,
	NumLock,
	NumSlash,
	NumAsterisk,
	NumMinus,
	Tab,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	OpenBracket,
	CloseBracket,
	Backslash,
	KeyboardDelete,
	End,
	PageDown,
	NumSeven,
	NumEight,
	NumNine,
	NumPlus,
	CapsLock,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Semicolon,
	Apostrophe,
	Enter,
	NumFour,
	NumFive,
	NumSix,
	LeftShift,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	Comma,
	Period,
	ForwardSlash,
	RightShift,
	ArrowUp,
	NumOne,
	NumTwo,
	NumThree,
	NumEnter,
	LeftControl,
	LeftWindows,
	LeftAlt,
	Space,
	RightAlt,
	RightWindows,
	ApplicationSelect,
	RightControl,
	ArrowLeft,
	ArrowDown,
	ArrowRight,
	NumZero,
	NumPeriod,
	G1,
	G2,
	G3,
	G4,
	G5,
	G6,
	G7,
	G8,
	G9,
	GLogo,
	GBadge
};


/**
 * Blueprint function library for Logitech LED SDK.
 */
UCLASS()
class ULogiLedBlueprintLibrary
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Initialize the Logitech LED SDK.
	 *
	 * @return true on success, false otherwise.
	 * @see LogiLedShutdown
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed")
	static bool LogiLedInitialize();

	/**
	 * Get the string representation of the given key.
	 *
	 * @param Key The key.
	 * @return The string representation.
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed")
	static FString LogiLedKeyToString(ELogiLedKeys Key);

	/**
	 * Set the target device type for future LogiLed calls.
	 *
	 * @param DeviceType The device type(s) to set.
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed")
	static bool LogiLedSetTargetDevice(ELogiLedDeviceType DeviceType);

	/**
	 * Shut down the Logitech LED SDK.
	 *
	 * @see LogiLedInitialize
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed")
	static void LogiLedShutdown();

public:

	/**
	 * Get the specified Boolean config option.
	 *
	 * @param ConfigPath Path to the config option to get.
	 * @param DefaultValue The option's default value.
	 * @return The Boolean config value.
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|Config")
	static bool LogiLedGetConfigOptionBool(const FString& ConfigPath, bool DefaultValue);

	/**
	 * Get the specified Color config option.
	 *
	 * @param ConfigPath Path to the config option to get.
	 * @param DefaultValue The option's default value.
	 * @return The color config value.
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|Config")
	static FLinearColor LogiLedGetConfigOptionColor(const FString& ConfigPath, FLinearColor DefaultValue);

	/**
	 * Set the label for the specified config option.
	 *
	 * @param ConfigPath Path to the config option.
	 * @param Label The option's label to set.
	 * @return true on success, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|Config")
	static bool LogiLedSetConfigOptionLabel(const FString& ConfigPath, FString Label);

	/**
	 * Get the specified numeric config option.
	 *
	 * @param ConfigPath Path to the config option to get.
	 * @param DefaultValue The option's default value.
	 * @return The numeric config value.
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|Config")
	static float LogiLedGetConfigOptionNumber(const FString& ConfigPath, float DefaultValue);

public:

	/**
	 * Play a flashing effect on the targeted devices.
	 *
	 * This function saves the current lighting, plays the flashing effect, and then
	 * restores the saved lighting.
	 *
	 * @param Color The flash color.
	 * @param Duration Duration of the effect.
	 * @param Interval Flashing interval.
	 * @return true on success, false otherwise.
	 * @see LogiLedFlashSingleKey, LogiLedPulseLighting, LogiLedSetLighting, LogiLedSetTargetDevice, LogiLedStopEffects
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|General")
	static void LogiLedFlashLighting(FLinearColor Color, FTimespan Duration, FTimespan Interval);

	/**
	 * Play a pulsing effect on the targeted devices.
	 *
	 * This function saves the current lighting, plays the flashing effect, and then
	 * restores the saved lighting.
	 *
	 * @param Color The pulse color.
	 * @param Duration Duration of the effect.
	 * @param Interval Flashing interval.
	 * @return true on success, false otherwise.
	 * @see LogiLedFlashLighting, LogiLedPulseSingleKey, LogiLedSetLighting, LogiLedSetTargetDevice, LogiLedStopEffects
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|General")
	static void LogiLedPulseLighting(FLinearColor Color, FTimespan Duration, FTimespan Interval);

	/**
	 * Restore a previously saved lighting.
	 *
	 * @see LogiLedRestoreLightingForKey, LogiLedSaveLighting, LogiLedSetTargetDevice
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|General")
	static void LogiLedRestoreLighting();

	/**
	 * Save the current lighting so that it can be restored.
	 *
	 * @see LogiLedRestoreLighting, LogiLedSaveLightingForKey, LogiLedSetTargetDevice
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|General")
	static void LogiLedSaveLighting();

	/**
	 * Set the lighting on the targeted devices.
	 *
	 * For devices that only support a single color, the highest percentage value given
	 * of the three colors will define the intensity. For monochrome backlighting device,
	 * Logitech Gaming Software will reduce proportionally the value of the highest color,
	 * according to the user hardware brightness setting.
	 *
	 * @param Color The light color to set.
	 * @see LogiLedFlashLighting, LogiLedPulseLighting, LogiLedSetTargetDevice
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|General")
	static void LogiLedSetLighting(FLinearColor Color);

	/**
	 * Play a color curve on the target device.
	 *
	 * @param ColorCurve The color curve to play.
	 * @see LogiLedAnimateSingleKey
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|General")
	static void LogiledSetLightingCurve(UCurveLinearColor* ColorCurve);

	/**
	 * Stop any active flashing, pulsing, or curve effect.
	 *
	 * @return true on success, false otherwise.
	 * @see LogiLedFlashLighting, LogiLedPulseLighting, LogiLedStopEffectsOnKey
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|General")
	static void LogiLedStopEffects();

public:

	/**
	 * Set a collection of keys to ignore when setting lighting from a bitmap.
	 *
	 * @param Keys The keys to exclude.
	 * @return true on success, false otherwise.
	 * @see LogiLedSetLightingFromTexture
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedExcludeKeysFromTexture(TArray<ELogiLedKeys> Keys);

	/**
	 * Play a flashing effect on the targeted devices.
	 *
	 * @param Key The key to flash.
	 * @param Color The flash color.
	 * @param Duration Duration of the effect.
	 * @param Interval Flashing interval.
	 * @return true on success, false otherwise.
	 * @see LogiLedFlashLighting. LogiLedPulseSingleKey, LogiLedSetTargetDevice, LogiLedStopEffects, LogiLedStopEffectsOnKey
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedFlashLightingForKey(ELogiLedKeys Key, FLinearColor Color, FTimespan Duration, FTimespan Interval);

	/**
	 * Play a pulsing effect on the specified key.
	 *
	 * @param Key The key to pulse.
	 * @param StartColor The pulse color to start with.
	 * @param EndColor The pulse color to finish with.
	 * @param Duration Duration of the effect.
	 * @param Infinite Whether to loop the effect until LogiLedStopEffectsOnKey or LogiLedStopEffects is called.
	 * @return true on success, false otherwise.
	 * @see LogiLedFlashSingleKey, LogiLedPulseLighting, LogiLedSetTargetDevice, LogiLedStopEffects, LogiLedStopEffectsOnKey
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedPulseLightingForKey(ELogiLedKeys Key, FLinearColor StartColor, FLinearColor EndColor, FTimespan Duration, bool Infinite);

	/**
	 * Restore a previously saved lighting for the specified key.
	 *
	 * @return true on success, false otherwise.
	 * @return true on success, false otherwise.
	 * @see LogiLedRestoreLighting, LogiLedSaveLightingForKey, LogiLedSetTargetDevice
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedRestoreLightingForKey(ELogiLedKeys Key);

	/**
	 * Save the current lighting for the specified key so that it can be restored.
	 *
	 * @return true on success, false otherwise.
	 * @return true on success, false otherwise.
	 * @see LogiLedRestoreLightingForKey, LogiLedSaveLighting, LogiLedSetTargetDevice
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedSaveLightingForKey(ELogiLedKeys Key);

	/**
	 * Play a color curve on the specified key.
	 *
	 * @param Key The key to play the color curve on.
	 * @param ColorCurve The color curve to play.
	 * @return true on success, false otherwise.
	 * @see LogiledAnimateLighting, LogiLedSetTargetDevice
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedSetLightingCurveForKey(ELogiLedKeys Key, UCurveLinearColor* ColorCurve);

	/**
	 * Set the lighting on the specified key.
	 *
	 * @param Key The key to set the lighting on.
	 * @param Color The lighting color to set.
	 *
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedSetLightingForKey(ELogiLedKeys Key, FLinearColor Color);

	/**
	 * Set the lighting of keys on the target device based on pixels in a texture.
	 *
	 * The texture is organized as an array of 21x6 RGBA pixels, representing the
	 * keys on the target device.
	 *
	 * @param Texture The texture containing the lighting color values.
	 * @return true on success, false otherwise.
	 * @see LogiLedExcludeKeysFromTexture
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedSetLightingFromTexture(UTexture* Texture);

	/**
	 * Stop any active flashing, pulsing, or curve effect on the specified key.
	 *
	 * @param Key The key to stop the effect on.
	 * @see LogiLedFlashSingleKey, LogiLedPulseSingleKey, LogiLedSetTargetDevice, LogiLedStopEffects
	 */
	UFUNCTION(BlueprintCallable, Category="LogiLed|PerKey")
	static void LogiLedStopEffectForKey(ELogiLedKeys Key);

private:

	/** State and timing manager. */
	static FLogiLedManager Manager;
};
