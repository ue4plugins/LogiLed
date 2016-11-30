// Copyright 2015 Headcrash Industries LLC. All Rights Reserved.

#include "LogiLedPrivate.h"

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"


DEFINE_LOG_CATEGORY(LogLogiLed);

#define LOCTEXT_NAMESPACE "FLogiLedModule"


/**
 * Implements the LogiLed module.
 */
class FLogiLedModule
	: public IModuleInterface
{
public:

	/** Default constructor. */
	FLogiLedModule()
		: Initialized(false)
	{ }

public:

	//~ IModuleInterface interface

	virtual void StartupModule() override
	{
#if LOGILED_SUPPORTED_PLATFORM
		// initialize Logitech SDK
		if (!::LogiLedInit())
		{
			UE_LOG(LogLogiLed, Error, TEXT("Failed to initialize Logitech LED SDK"));
			return;
		}
#else
		return;
#endif //LOGILED_SUPPORTED_PLATFORM

		int Major, Minor, Build;

		if (::LogiLedGetSdkVersion(&Major, &Minor, &Build))
		{
			UE_LOG(LogLogiLed, Log, TEXT("Initialized Logitech LED SDK %i.%i.%i."), Major, Minor, Build);
		}
		else
		{
			UE_LOG(LogLogiLed, Log, TEXT("Initialized Logitech LED SDK (unknown version)"));
		}

		Initialized = true;
	}

	virtual void ShutdownModule() override
	{
		if (!Initialized)
		{
			return;
		}

#if LOGILED_SUPPORTED_PLATFORM
		// shut down SDK
		::LogiLedShutdown();
#endif

		Initialized = false;
	}

private:

	/** Whether the module has been initialized. */
	bool Initialized;
};


IMPLEMENT_MODULE(FLogiLedModule, LogiLed);


#undef LOCTEXT_NAMESPACE
