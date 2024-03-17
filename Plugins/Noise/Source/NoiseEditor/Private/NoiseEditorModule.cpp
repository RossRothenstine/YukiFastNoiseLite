#include "NoiseEditorModule.h"

#include "NoiseEditor.h"
#include "NoiseEditorCommands.h"
#include "NoiseEditorStyle.h"

class FNoiseEditorModule : public INoiseEditorModule
{
	TSharedRef<INoiseEditor> CreateNoiseEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UNoise* ObjectToEdit) override;
	void StartupModule() override;
	void ShutdownModule() override;
};

#define LOCTEXT_NAMESPACE "FNoiseEditorModule"

TSharedRef<INoiseEditor> FNoiseEditorModule::CreateNoiseEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UNoise* ObjectToEdit)
{
	TSharedRef<FNoiseEditor> NewNoiseEditor(new FNoiseEditor());
	NewNoiseEditor->InitEditor(Mode, InitToolkitHost, ObjectToEdit);
	return NewNoiseEditor;
}

void FNoiseEditorModule::StartupModule()
{
	FNoiseEditorStyle::Register();
	FNoiseEditorCommands::Register();
}

void FNoiseEditorModule::ShutdownModule()
{
    FNoiseEditorCommands::Unregister();
	FNoiseEditorStyle::Unregister();
}



#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FNoiseEditorModule, NoiseEditor)
