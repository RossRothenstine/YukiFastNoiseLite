#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class INoiseEditor;
class INoiseEditorModule : public IModuleInterface
{
public:
	static INoiseEditorModule& Get() { return FModuleManager::LoadModuleChecked<INoiseEditorModule>("NoiseEditor"); }
	
	virtual TSharedRef<INoiseEditor> CreateNoiseEditor(const EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost,
		class UNoise* ObjectToEdit) = 0;
};
