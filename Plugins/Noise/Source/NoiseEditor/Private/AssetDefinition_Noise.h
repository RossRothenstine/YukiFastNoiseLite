// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"

#include "AssetDefinition_Noise.generated.h"

/**
 * 
 */
UCLASS()
class NOISEEDITOR_API UAssetDefinition_Noise : public UAssetDefinitionDefault
{
	GENERATED_BODY()

	FText GetAssetDisplayName() const override;
	FLinearColor GetAssetColor() const override;
	TSoftClassPtr<UObject> GetAssetClass() const override;
	TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
};
