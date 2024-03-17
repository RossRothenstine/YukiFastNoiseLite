// Fill out your copyright notice in the Description page of Project Settings.

#include "NoiseFactory.h"

#include "Noise.h"

UNoiseFactory::UNoiseFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UNoise::StaticClass();
}
UObject* UNoiseFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNoise>(InParent, InClass, InName, Flags);
}
