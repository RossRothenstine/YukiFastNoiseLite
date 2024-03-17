// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NOISEEDITOR_API FNoiseEditorStyle : public FSlateStyleSet
{
public:
	FNoiseEditorStyle();
	
	static FName GetEditorStyleSetName();
    static FNoiseEditorStyle& Get();

	static void Register();
	static void Unregister();
};
