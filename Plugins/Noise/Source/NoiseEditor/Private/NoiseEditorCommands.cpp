// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseEditorCommands.h"

#include "NoiseEditorStyle.h"

#define LOCTEXT_NAMESPACE "NoiseEditorCommands"

FNoiseEditorCommands::FNoiseEditorCommands()
	: TCommands<FNoiseEditorCommands>("NoiseEditor", NSLOCTEXT("Contexts", "NoiseEditor", "Noise Editor"), NAME_None, FNoiseEditorStyle::GetEditorStyleSetName())
{
}
void FNoiseEditorCommands::RegisterCommands()
{
	UI_COMMAND(SaveTexture, "Save Texture", "Saves the Noise Texture", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
