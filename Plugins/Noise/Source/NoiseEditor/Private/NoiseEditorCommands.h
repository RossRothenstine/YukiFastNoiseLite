// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NOISEEDITOR_API FNoiseEditorCommands
    : public TCommands<FNoiseEditorCommands>
{
public:
	FNoiseEditorCommands();

	void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> SaveTexture;

};
