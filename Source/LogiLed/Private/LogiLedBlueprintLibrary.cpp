// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LogiLedBlueprintLibrary.h"

#include "Classes/Curves/CurveLinearColor.h"
#include "Classes/Engine/Texture.h"
#include "TextureResource.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"


FLogiLedManager ULogiLedBlueprintLibrary::Manager;


/* Local constants
 *****************************************************************************/

const uint32 LogiLedKeyName[] = {
	0x01, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x57, 0x58, 0x137, 0x46, 0x145,
	0x29, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,	0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x152, 0x147,
	0x149, 0x45, 0x135, 0x37, 0x4A, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
	0x1A, 0x1B, 0x2B, 0x153, 0x14F, 0x151, 0x47, 0x48, 0x49, 0x4E, 0x3A, 0x1E, 0x1F, 0x20, 0x21, 0x22,
	0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x1C, 0x4B, 0x4C, 0x4D, 0x2A, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x148, 0x4F, 0x50, 0x51, 0x11C, 0x1D, 0x15B, 0x38, 0x39, 0x138,
	0x15C, 0x15D, 0x11D, 0x14B, 0x150, 0x14D, 0x52, 0x53, 0xFFF1, 0xFFF2, 0xFFF3, 0xFFF4, 0xFFF5, 0xFFF6,
	0xFFF7, 0xFFF8, 0xFFF9, 0xFFFF1, 0xFFFF2
};


/* ULogiLedBlueprintLibrary interface (generic functions)
 *****************************************************************************/

bool ULogiLedBlueprintLibrary::LogiLedInitialize()
{
	if (!::LogiLedInit())
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to initialize Logitech LED SDK"));
		return false;
	}

	return true;
}


FString ULogiLedBlueprintLibrary::LogiLedKeyToString(ELogiLedKeys Key)
{
	static const UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ELogiLedKeys"));
	check(Enum);

	return Enum->GetNameStringByValue((int64)Key);
}


bool ULogiLedBlueprintLibrary::LogiLedSetTargetDevice(ELogiLedDeviceType DeviceType)
{
	int32 TargetDevice = 0;

	switch (DeviceType)
	{
	case ELogiLedDeviceType::All: TargetDevice = LOGI_DEVICETYPE_ALL; break;
	case ELogiLedDeviceType::Monochrome: TargetDevice = LOGI_DEVICETYPE_MONOCHROME; break;
	case ELogiLedDeviceType::PerKeyRgb: TargetDevice = LOGI_DEVICETYPE_PERKEY_RGB; break;
	case ELogiLedDeviceType::Rgb: TargetDevice = LOGI_DEVICETYPE_RGB; break;
	}

	if (!::LogiLedSetTargetDevice(TargetDevice))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to set target device"));
		return false;
	}

	return true;
}


void ULogiLedBlueprintLibrary::LogiLedShutdown()
{
	::LogiLedShutdown();
}


/* ULogiLedBlueprintLibrary interface (configuration functions)
 *****************************************************************************/

bool ULogiLedBlueprintLibrary::LogiLedGetConfigOptionBool(const FString& ConfigPath, bool DefaultValue)
{
	if (!::LogiLedGetConfigOptionBool(*ConfigPath, &DefaultValue))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to get Boolean config option for %s"), *ConfigPath);
	}

	return DefaultValue;
}


FLinearColor ULogiLedBlueprintLibrary::LogiLedGetConfigOptionColor(const FString& ConfigPath, FLinearColor DefaultValue)
{
	FColor Default = DefaultValue.ToFColor(false);

	int R = Default.R;
	int G = Default.G;
	int B = Default.B;

	if (::LogiLedGetConfigOptionColor(*ConfigPath, &R, &G, &B))
	{
		Default.R = R;
		Default.G = G;
		Default.B = B;
	}
	else
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to get color config option for %s"), *ConfigPath);
	}

return FLinearColor(Default);
}


bool ULogiLedBlueprintLibrary::LogiLedSetConfigOptionLabel(const FString& ConfigPath, FString Label)
{
	if (!::LogiLedSetConfigOptionLabel(*ConfigPath, const_cast<wchar_t*>(*Label)))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to set label for config option %s"), *ConfigPath);
		return false;
	}

	return true;
}


float ULogiLedBlueprintLibrary::LogiLedGetConfigOptionNumber(const FString& ConfigPath, float DefaultValue)
{
	double OutValue = DefaultValue;

	if (!::LogiLedGetConfigOptionNumber(*ConfigPath, &OutValue))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to get numeric config option for %s"), *ConfigPath);
	}

	return (float)OutValue;
}


/* ULogiLedBlueprintLibrary interface (global lighting functions)
 *****************************************************************************/

void ULogiLedBlueprintLibrary::LogiLedFlashLighting(FLinearColor Color, FTimespan Duration, FTimespan Interval)
{
	const FLinearColor Percentage = Color.GetClamped() * 100.0f;

	if (!::LogiLedFlashLighting(Percentage.R, Percentage.G, Percentage.B, (int)Duration.GetTotalMilliseconds(), (int)Interval.GetTotalMilliseconds()))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to flash lighting with color %s for duration %s with interval %s"), *Color.ToString(), *Duration.ToString(), *Interval.ToString());
	}
}


void ULogiLedBlueprintLibrary::LogiLedPulseLighting(FLinearColor Color, FTimespan Duration, FTimespan Interval)
{
	const FLinearColor Percentage = Color.GetClamped() * 100.0f;

	if (!::LogiLedPulseLighting(Percentage.R, Percentage.G, Percentage.B, (int)Duration.GetTotalMilliseconds(), (int)Interval.GetTotalMilliseconds()))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to pulse lighting with color %s for duration %s with interval %s"), *Color.ToString(), *Duration.ToString(), *Interval.ToString());
	}
}


void ULogiLedBlueprintLibrary::LogiLedRestoreLighting()
{
	if (!::LogiLedRestoreLighting())
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to restore saved lighting"));
	}
}


void ULogiLedBlueprintLibrary::LogiLedSaveLighting()
{
	if (!::LogiLedSaveCurrentLighting())
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to save current lighting"));
	}
}


void ULogiLedBlueprintLibrary::LogiLedSetLighting(FLinearColor Color)
{
	const FLinearColor Percentage = Color.GetClamped() * 100.0f;

	if (!::LogiLedSetLighting(Percentage.R, Percentage.G, Percentage.B))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to set lighting to %s"), *Color.ToString());
	}
}


void ULogiLedBlueprintLibrary::LogiledSetLightingCurve(UCurveLinearColor* ColorCurve)
{
	Manager.PlayAnimation(ColorCurve);
}


void ULogiLedBlueprintLibrary::LogiLedStopEffects()
{
	Manager.StopAnimations();

	if (!::LogiLedStopEffects())
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to stop effects"));
	}
}


/* ULogiLedBlueprintLibrary interface (per-key functions)
 *****************************************************************************/

void ULogiLedBlueprintLibrary::LogiLedExcludeKeysFromTexture(TArray<ELogiLedKeys> Keys)
{
	TArray<LogiLed::KeyName> KeyNames;

	for (auto Key : Keys)
	{
		KeyNames.Add((LogiLed::KeyName)LogiLedKeyName[(int)Key]);
	}

	if (!::LogiLedExcludeKeysFromBitmap(KeyNames.GetData(), KeyNames.Num()))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to exclude keys from bitmap"));
	}
}


void ULogiLedBlueprintLibrary::LogiLedFlashLightingForKey(ELogiLedKeys Key, FLinearColor Color, FTimespan Duration, FTimespan Interval)
{
	const FLinearColor Percentage = Color.GetClamped() * 100.0f;

	if (!::LogiLedFlashSingleKey(
		(LogiLed::KeyName)LogiLedKeyName[(int)Key],
		Percentage.R, Percentage.G, Percentage.B,
		(int)Duration.GetTotalMilliseconds(),
		(int)Interval.GetTotalMilliseconds()
	))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to flash lighting for key %s"), *LogiLedKeyToString(Key));
	}
}


void ULogiLedBlueprintLibrary::LogiLedFlashLightingForKeys(const TArray<ELogiLedKeys> Keys, FLinearColor Color, FTimespan Duration, FTimespan Interval)
{
	for (const auto& Key : Keys)
	{
		LogiLedFlashLightingForKey(Key, Color, Duration, Interval);
	}
}


void ULogiLedBlueprintLibrary::LogiLedPulseLightingForKey(ELogiLedKeys Key, FLinearColor StartColor, FLinearColor EndColor, FTimespan Duration, bool Infinite)
{
	const FLinearColor StartPercentage = StartColor.GetClamped() * 100.0f;
	const FLinearColor EndPercentage = EndColor.GetClamped() * 100.0f;

	if (!::LogiLedPulseSingleKey(
		(LogiLed::KeyName)LogiLedKeyName[(int)Key],
		StartPercentage.R, StartPercentage.G, StartPercentage.B,
		EndPercentage.R, EndPercentage.G, EndPercentage.B,
		(int)Duration.GetTotalMilliseconds(),
		Infinite
	))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to pulse lighting for key %s"), *LogiLedKeyToString(Key));
	}
}


void ULogiLedBlueprintLibrary::LogiLedPulseLightingForKeys(const TArray<ELogiLedKeys>& Keys, FLinearColor StartColor, FLinearColor EndColor, FTimespan Duration, bool Infinite)
{
	for (const auto& Key : Keys)
	{
		LogiLedPulseLightingForKey(Key, StartColor, EndColor, Duration, Infinite);
	}
}


void ULogiLedBlueprintLibrary::LogiLedRestoreLightingForKey(ELogiLedKeys Key)
{
	if (!::LogiLedRestoreLightingForKey((LogiLed::KeyName)LogiLedKeyName[(int)Key]))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to restore lighting for key %s"), *LogiLedKeyToString(Key));
	}
}


void ULogiLedBlueprintLibrary::LogiLedRestoreLightingForKeys(const TArray<ELogiLedKeys>& Keys)
{
	for (const auto& Key : Keys)
	{
		LogiLedRestoreLightingForKey(Key);
	}
}


void ULogiLedBlueprintLibrary::LogiLedSaveLightingForKey(ELogiLedKeys Key)
{
	if (!::LogiLedSaveLightingForKey((LogiLed::KeyName)LogiLedKeyName[(int)Key]))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to save lighting for key %s"), *LogiLedKeyToString(Key));
	}
}


void ULogiLedBlueprintLibrary::LogiLedSaveLightingForKeys(const TArray<ELogiLedKeys>& Keys)
{
	for (const auto& Key : Keys)
	{
		LogiLedSaveLightingForKey(Key);
	}
}


void ULogiLedBlueprintLibrary::LogiLedSetLightingCurveForKey(ELogiLedKeys Key, UCurveLinearColor* ColorCurve)
{
	Manager.PlayAnimation((LogiLed::KeyName)LogiLedKeyName[(int)Key], ColorCurve);
}


void ULogiLedBlueprintLibrary::LogiLedSetLightingCurveForKeys(const TArray<ELogiLedKeys>& Keys, UCurveLinearColor* ColorCurve)
{
	for (const auto& Key : Keys)
	{
		LogiLedSetLightingCurveForKey(Key, ColorCurve);
	}
}


void ULogiLedBlueprintLibrary::LogiLedSetLightingForKey(ELogiLedKeys Key, FLinearColor Color)
{
	const FLinearColor Percentage = Color.GetClamped() * 100.0f;

	if (!::LogiLedSetLightingForKeyWithKeyName((LogiLed::KeyName)LogiLedKeyName[(int)Key], Percentage.R, Percentage.G, Percentage.B))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to set lighting to %s for key %s"), *Color.ToString(), *LogiLedKeyToString(Key));
	}
}


void ULogiLedBlueprintLibrary::LogiLedSetLightingForKeys(const TArray<ELogiLedKeys>& Keys, FLinearColor Color)
{
	for (const auto& Key : Keys)
	{
		LogiLedSetLightingForKey(Key, Color);
	}
}


void ULogiLedBlueprintLibrary::LogiLedSetLightingFromTexture(UTexture* Texture)
{
	if ((Texture == nullptr) || (Texture->Resource == nullptr))
	{
		return;
	}

	uint32 Height = Texture->Resource->GetSizeY();
	uint32 Width = Texture->Resource->GetSizeX();

	if ((Height != LOGI_LED_BITMAP_HEIGHT) || (Width != LOGI_LED_BITMAP_WIDTH))
	{
		UE_LOG(LogLogiLed, Warning, TEXT("Lighting texture must be %ix%i, but it is %ix%i"), LOGI_LED_BITMAP_WIDTH, LOGI_LED_BITMAP_HEIGHT, Width, Height);
	}

	// @todo gmp: logiled: implement lighting from texture
}


void ULogiLedBlueprintLibrary::LogiLedStopEffectForKey(ELogiLedKeys Key)
{
	auto KeyName = (LogiLed::KeyName)LogiLedKeyName[(int)Key];
	Manager.StopAnimations(KeyName);

	if (!::LogiLedStopEffectsOnKey(KeyName))
	{
		UE_LOG(LogLogiLed, Verbose, TEXT("Failed to stop effects for key %s"), *LogiLedKeyToString(Key));
	}
}


void ULogiLedBlueprintLibrary::LogiLedStopEffectForKeys(const TArray<ELogiLedKeys>& Keys)
{
	for (const auto& Key : Keys)
	{
		LogiLedStopEffectForKey(Key);
	}
}
