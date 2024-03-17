// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

/**
 * 
 */
class NOISEEDITOR_API FNoiseTextureViewportClient
	: public FViewportClient
	, public FGCObject
{
public:
	FNoiseTextureViewportClient(TWeakPtr<class INoiseEditor> InNoiseEditor, TWeakPtr<class SNoiseTextureViewport> InViewport);
	~FNoiseTextureViewportClient();

	// FViewportClient interface~
	void Draw(FViewport* Viewport, FCanvas* Canvas) override;

	// FGCObject interface~
	FString GetReferencerName() const override;
	void AddReferencedObjects(FReferenceCollector& Collector) override;

private:
	void DrawCheckerboard(FViewport* Viewport, FCanvas* Canvas);
	void DrawTexture(FViewport* Viewport, FCanvas* Canvas);
	
	TObjectPtr<UTexture2D> CheckerboardTexture;
	
	TWeakPtr<class INoiseEditor> NoiseEditor;
	TWeakPtr<class SNoiseTextureViewport> TextureViewport;
};
