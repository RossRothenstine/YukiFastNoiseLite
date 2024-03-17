// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseEditorStyle.h"

#include "Styling/SlateStyleRegistry.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)

FName NAME_NoiseEditorStyle = FName("NoiseEditorStyle");

FNoiseEditorStyle::FNoiseEditorStyle()
	: FSlateStyleSet(NAME_NoiseEditorStyle)
{
	SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));
	
	Set("NoiseEditor.SaveTexture", new IMAGE_BRUSH("Icons/icon_SaveAsset_40x", CoreStyleConstants::Icon40x40));
}
FName FNoiseEditorStyle::GetEditorStyleSetName()
{
	return NAME_NoiseEditorStyle;
}

FNoiseEditorStyle& FNoiseEditorStyle::Get()
{
	static FNoiseEditorStyle Instance;
	return Instance;
}
void FNoiseEditorStyle::Register()
{
	FSlateStyleRegistry::RegisterSlateStyle(Get());
}
void FNoiseEditorStyle::Unregister()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(Get());
}
