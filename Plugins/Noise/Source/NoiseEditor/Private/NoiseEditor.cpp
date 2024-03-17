// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseEditor.h"

#include "Noise.h"
#include "NoiseEditorCommands.h"
#include "SNoiseTextureViewport.h"

const FName NoiseAppIdentifier(TEXT("NoiseEditorApp"));
const FName ViewportPanelTabId(TEXT("Viewport"));
const FName PropertiesPanelTabId(TEXT("Properties"));


#define LOCTEXT_NAMESPACE "NoiseEditor"

void FNoiseEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UNoise* ObjectToEdit)
{
	Noise = ObjectToEdit;
	Texture = UTexture2D::CreateTransient(256, 256, PF_R8G8B8A8);
	UpdateNoiseTexture();

	auto StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_Noise_Layout_v1")
	->AddArea(
		// Primary Area.
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)

		// Main Content
		->Split
		(
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			->Split
			(
				// Texture Viewer.
			FTabManager::NewStack()
				->SetSizeCoefficient(0.7f)
				->SetHideTabWell(true)
				->AddTab(ViewportPanelTabId, ETabState::OpenedTab)
			)
			->Split
			(
				// Properties Viewer.
				FTabManager::NewStack()
				->SetSizeCoefficient(0.3f)
				->AddTab(PropertiesPanelTabId, ETabState::OpenedTab)
			)
		)
	);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, NoiseAppIdentifier, StandaloneDefaultLayout, 
		bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, ObjectToEdit);

	ExtendToolbar();
	
	RegenerateMenusAndToolbars();
}
void FNoiseEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_NoiseEditor", "Noise Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();
	
	INoiseEditor::RegisterTabSpawners(InTabManager);

	TabManager->RegisterTabSpawner(PropertiesPanelTabId, FOnSpawnTab::CreateSP(this, &FNoiseEditor::SpawnTab_Properties))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Properties"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));
	
	TabManager->RegisterTabSpawner(ViewportPanelTabId, FOnSpawnTab::CreateSP(this, &FNoiseEditor::SpawnTab_Viewport))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));
}
TObjectPtr<UTexture2D> FNoiseEditor::GetTexture() const
{
	return Texture;
}

TSharedRef<SDockTab> FNoiseEditor::SpawnTab_Properties(const FSpawnTabArgs& SpawnTabArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NotifyHook = this;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;

	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(Noise);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("PropertiesTitle", "Properties"))
		.TabRole(ETabRole::PanelTab)
		[
			DetailsView.ToSharedRef()
		];
	return SpawnedTab;
}

TSharedRef<SDockTab> FNoiseEditor::SpawnTab_Viewport(const FSpawnTabArgs& SpawnTabArgs)
{
	Viewport = SNew(SNoiseTextureViewport, SharedThis(this));
	
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("ViewportTitle", "Viewport"))
		.TabRole(PanelTab)
		[
			Viewport.ToSharedRef()
		];
	return SpawnedTab;
}
void FNoiseEditor::UpdateNoiseTexture()
{
	FByteBulkData* BulkData = &Texture->GetPlatformData()->Mips[0].BulkData;
	uint8* Data = static_cast<uint8*>(BulkData->Lock(LOCK_READ_WRITE));

	for (int X = 0; X < 256; X++)
	{
		for (int Y = 0; Y < 256; Y++)
		{
			int Pixel = (X * 256 * 4) + Y * 4;
			float Value = Noise->GetNoise2D(X, Y);
			// Normalize Noise to between [0, 1]
			float Normalized = (Value + 1.0f) / 2.0f;
			int PixelValue = Normalized * 255;
			Data[Pixel + 0] = PixelValue;
			Data[Pixel + 1] = PixelValue;
			Data[Pixel + 2] = PixelValue;
			Data[Pixel + 3] = 255;
		}
	}

	BulkData->Unlock();
	Texture->UpdateResource();
}
void FNoiseEditor::ExtendToolbar()
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShared<FExtender>();
	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP(this, &FNoiseEditor::FillToolbar)
	);
	AddToolbarExtender(ToolbarExtender);
}
void FNoiseEditor::FillToolbar(FToolBarBuilder& ToolBarBuilder)
{
	ToolBarBuilder.BeginSection("NoiseMisc");
	ToolBarBuilder.AddToolBarButton(FNoiseEditorCommands::Get().SaveTexture);
	ToolBarBuilder.EndSection();
}

FLinearColor FNoiseEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Blue;
}

FName FNoiseEditor::GetToolkitFName() const
{
	return FName("NoiseEditor");
}

FText FNoiseEditor::GetBaseToolkitName() const
{
	return NSLOCTEXT("NoiseEditor", "AppLabel", "Noise Editor");
}

FString FNoiseEditor::GetWorldCentricTabPrefix() const
{
	return NSLOCTEXT("NoiseEditor", "WorldCentricTabPrefix", "Noise").ToString();
}

void FNoiseEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(Noise);
	Collector.AddReferencedObject(Texture);
	Viewport->AddReferencedObjects(Collector);
}

FString FNoiseEditor::GetReferencerName() const
{
	return "FNoiseEditor";
}
void FNoiseEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	UpdateNoiseTexture();
}

#undef LOCTEXT_NAMESPACE
