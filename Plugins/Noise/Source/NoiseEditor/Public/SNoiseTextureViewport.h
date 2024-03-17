// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class INoiseEditor;
/**
 * 
 */
class NOISEEDITOR_API SNoiseTextureViewport : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNoiseTextureViewport) { }
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedRef<INoiseEditor>& InNoiseEditor);

	void AddReferencedObjects(FReferenceCollector& Collector);


	// SWidget interface~
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	TWeakPtr<INoiseEditor> NoiseEditor;

	TSharedPtr<class FNoiseTextureViewportClient> ViewportClient;
	TSharedPtr<FSceneViewport> Viewport;
	TSharedPtr<SViewport> ViewportWidget;
};
