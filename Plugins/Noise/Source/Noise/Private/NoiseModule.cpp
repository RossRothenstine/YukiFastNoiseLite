// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoiseModule.h"

class FNoiseModule : public INoiseModule
{
	void StartupModule() override;
	void ShutdownModule() override;
};

#define LOCTEXT_NAMESPACE "FNoiseModule"

void FNoiseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FNoiseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNoiseModule, Noise)
