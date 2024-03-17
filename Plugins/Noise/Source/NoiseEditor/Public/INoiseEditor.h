#pragma once

#include "CoreMinimal.h"

#include "Toolkits/AssetEditorToolkit.h"

class INoiseEditor : public FAssetEditorToolkit
{
public:
	virtual TObjectPtr<UTexture2D> GetTexture() const = 0;
};
