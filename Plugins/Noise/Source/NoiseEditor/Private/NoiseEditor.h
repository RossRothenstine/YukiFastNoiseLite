// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "INoiseEditor.h"

/**
 * 
 */
class NOISEEDITOR_API FNoiseEditor
	: public INoiseEditor
	, public FNotifyHook
	, public FGCObject
{
public:
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, class UNoise* ObjectToEdit);

	// FAssetEditorToolkit interface~
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	// INoiseEditor interface~
	TObjectPtr<UTexture2D> GetTexture() const override;
	FLinearColor GetWorldCentricTabColorScale() const override;
	FName GetToolkitFName() const override;
	FText GetBaseToolkitName() const override;
	FString GetWorldCentricTabPrefix() const override;

	// FGCObject interface~
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;

	// FNotifyHook interface~
	void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;

private:
	TSharedRef<class SDockTab> SpawnTab_Properties(const FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& SpawnTabArgs);
	void UpdateNoiseTexture();
	void ExtendToolbar();
	void FillToolbar(FToolBarBuilder& ToolBarBuilder);
	
	TObjectPtr<UNoise> Noise;
	TSharedPtr<class IDetailsView> DetailsView;
	TSharedPtr<class SNoiseTextureViewport> Viewport;
	TObjectPtr<UTexture2D> Texture;
};
