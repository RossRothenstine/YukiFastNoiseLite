// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NoiseFactory.generated.h"

/**
 * 
 */
UCLASS()
class NOISEEDITOR_API UNoiseFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNoiseFactory(); 
	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
