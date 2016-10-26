// Copyright 2015 Headcrash Industries LLC. All Rights Reserved.

#pragma once

#define LOGILED_SUPPORTED_PLATFORM (PLATFORM_WINDOWS)


#include "LogitechLEDLib.h"

#include "Runtime/Core/Public/Core.h"
#include "Runtime/CoreUObject/Public/CoreUObject.h"
// start missing CurveLinearColor.h dependencies
#include "Runtime/Engine/Public/Engine.h"
#include "Runtime/Engine/Classes/Curves/CurveBase.h"
// end dependencies
#include "Runtime/Engine/Classes/Curves/CurveLinearColor.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"


DECLARE_LOG_CATEGORY_EXTERN(LogLogiLed, Log, All);
