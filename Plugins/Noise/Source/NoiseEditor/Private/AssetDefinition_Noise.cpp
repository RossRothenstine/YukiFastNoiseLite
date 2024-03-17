// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetDefinition_Noise.h"

#include "NoiseEditorModule.h"
#include "NoiseModule.h"
#include "Noise/Public/Noise.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

FText UAssetDefinition_Noise::GetAssetDisplayName() const
{
	return LOCTEXT("FAssetTypeActions_Noise", "Noise");
}

FLinearColor UAssetDefinition_Noise::GetAssetColor() const
{
	return FLinearColor(0.0f, 0.5f, 1.0f);
}

TSoftClassPtr<UObject> UAssetDefinition_Noise::GetAssetClass() const
{
	return UNoise::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_Noise::GetAssetCategories() const
{
	static FAssetCategoryPath Categories[] =
		{
		EAssetCategoryPaths::Misc
		};
	return Categories;
}

EAssetCommandResult UAssetDefinition_Noise::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	INoiseEditorModule& EditorModule = FModuleManager::LoadModuleChecked<INoiseEditorModule>("NoiseEditor");
	for (UNoise* Noise : OpenArgs.LoadObjects<UNoise>())
	{
		EditorModule.CreateNoiseEditor(EToolkitMode::Standalone, OpenArgs.ToolkitHost, Noise);
	}
	return EAssetCommandResult::Handled;
}

#undef LOCTEXT_NAMESPACE
