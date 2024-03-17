// Fill out your copyright notice in the Description page of Project Settings.


#include "SNoiseTextureViewport.h"
#include "INoiseEditor.h"
#include "NoiseTextureViewportClient.h"
#include "SlateOptMacros.h"
#include "Slate/SceneViewport.h"
#include "Widgets/SViewport.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SNoiseTextureViewport::Construct(const FArguments& InArgs, const TSharedRef<INoiseEditor>& InNoiseEditor)
{
	NoiseEditor = InNoiseEditor;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.Padding(5.0f, 0.0f)
			[
				SAssignNew(ViewportWidget, SViewport)
				.EnableGammaCorrection(false)
				.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
				.ShowEffectWhenDisabled(false)
				.EnableBlending(true)
			]
		]
	];

	ViewportClient = MakeShareable(new FNoiseTextureViewportClient(NoiseEditor, SharedThis(this)));
	Viewport = MakeShareable(new FSceneViewport(ViewportClient.Get(), ViewportWidget));
	ViewportWidget->SetViewportInterface(Viewport.ToSharedRef());
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SNoiseTextureViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	ViewportClient->AddReferencedObjects(Collector);
}
void SNoiseTextureViewport::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	Viewport->Invalidate();
}
