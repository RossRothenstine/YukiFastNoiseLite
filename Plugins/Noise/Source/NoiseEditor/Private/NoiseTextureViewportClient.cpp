// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseTextureViewportClient.h"

#include "CanvasTypes.h"
#include "ImageUtils.h"
#include "INoiseEditor.h"

FNoiseTextureViewportClient::FNoiseTextureViewportClient(TWeakPtr<INoiseEditor> InNoiseEditor, TWeakPtr<SNoiseTextureViewport> InViewport)
	: NoiseEditor(InNoiseEditor)
	, TextureViewport(InViewport)
{
	CheckerboardTexture = FImageUtils::CreateCheckerboardTexture();
}
FNoiseTextureViewportClient::~FNoiseTextureViewportClient()
{
	if (CheckerboardTexture)
	{
		if (CheckerboardTexture->GetResource())
		{
			CheckerboardTexture->ReleaseResource();
		}
		CheckerboardTexture->MarkAsGarbage();
		CheckerboardTexture = nullptr;
	}
}

void FNoiseTextureViewportClient::Draw(FViewport* Viewport, FCanvas* Canvas)
{
	DrawCheckerboard(Viewport, Canvas);
	DrawTexture(Viewport, Canvas);
}

void FNoiseTextureViewportClient::DrawCheckerboard(FViewport* Viewport, FCanvas* Canvas)
{
	FIntPoint ViewportXY = Viewport->GetSizeXY();
	const float CheckerboardSizeX = (float)FMath::Max<int32>(1, CheckerboardTexture->GetSizeX());
	const float CheckerboardSizeY = (float)FMath::Max<int32>(1, CheckerboardTexture->GetSizeX());
	Canvas->DrawTile(0.0f, 0.0f, ViewportXY.X, ViewportXY.Y, 0.0f, 0.0f, ViewportXY.X / CheckerboardSizeX, ViewportXY.Y / CheckerboardSizeY, FLinearColor::White, CheckerboardTexture->GetResource());
}
void FNoiseTextureViewportClient::DrawTexture(FViewport* Viewport, FCanvas* Canvas)
{
	UTexture2D* Texture = NoiseEditor.Pin()->GetTexture();

	Texture->SetForceMipLevelsToBeResident(30.0f);
	Texture->WaitForStreaming();
	
	FIntPoint ViewportXY = Viewport->GetSizeXY();
	float X = ViewportXY.X * 0.5f - Texture->GetSizeX() * 0.5f;
	float Y = ViewportXY.Y * 0.5f - Texture->GetSizeY() * 0.5f;

	Canvas->DrawTile(X, Y, Texture->GetSizeX(), Texture->GetSizeY(), 0.0f, 0.0f, 1.0f, 1.0f, FLinearColor::White, Texture->GetResource());
}

FString FNoiseTextureViewportClient::GetReferencerName() const
{
	return "FNoiseTextureViewportClient";
}
void FNoiseTextureViewportClient::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(CheckerboardTexture);
}
