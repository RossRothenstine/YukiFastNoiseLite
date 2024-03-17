// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Noise.generated.h"

UENUM(BlueprintType)
enum class EFastNoiseLiteNoiseType : uint8
{
	NoiseType_OpenSimplex2,
	NoiseType_OpenSimplex2S,
	NoiseType_Cellular,
	NoiseType_Perlin,
	NoiseType_ValueCubic,
	NoiseType_Value
};

UENUM(BlueprintType)
enum class EFastNoiseLiteRotationType3D : uint8
{
	RotationType3D_None,
	RotationType3D_ImproveXYPlanes,
	RotationType3D_ImproveXZPlanes
};

UENUM(BlueprintType)
enum class EFastNoiseLiteFractalType : uint8
{
	FractalType_None,
	FractalType_FBm,
	FractalType_Ridged,
	FractalType_PingPong,
	FractalType_DomainWarpProgressive,
	FractalType_DomainWarpIndependent
};

UENUM(BlueprintType)
enum class EFastNoiseLiteCellularDistanceFunction : uint8
{
	CellularDistanceFunction_Euclidean,
	CellularDistanceFunction_EuclideanSq,
	CellularDistanceFunction_Manhattan,
	CellularDistanceFunction_Hybrid
};

UENUM(BlueprintType)
enum class EFastNoiseLiteCellularReturnType : uint8
{
	CellularReturnType_CellValue,
	CellularReturnType_Distance,
	CellularReturnType_Distance2,
	CellularReturnType_Distance2Add,
	CellularReturnType_Distance2Sub,
	CellularReturnType_Distance2Mul,
	CellularReturnType_Distance2Div
};

UENUM(BlueprintType)
enum class EFastNoiseLiteDomainWarpType : uint8
{
	DomainWarpType_OpenSimplex2,
	DomainWarpType_OpenSimplex2Reduced,
	DomainWarpType_BasicGrid
};

/**
 * A Noise Object that proxies to FastNoiseLite.
 */
UCLASS(Category = "Noise", BlueprintType)
class NOISE_API UNoise : public UObject
{
	GENERATED_BODY()
public:
	UNoise();

	UFUNCTION(BlueprintCallable)
	void SetSeed(int32 InSeed);

	UFUNCTION(BlueprintCallable)
	void SetFrequency(float InFrequency);

	UFUNCTION(BlueprintCallable)
	void SetNoiseType(EFastNoiseLiteNoiseType InNoiseType);

	UFUNCTION(BlueprintCallable)
	void SetRotationType3D(EFastNoiseLiteRotationType3D InRotationType3D);

	UFUNCTION(BlueprintCallable)
	void SetFractalOctaves(int32 InOctaves);
	
	UFUNCTION(BlueprintCallable)
	void SetFractalType(EFastNoiseLiteFractalType InFractalType);

	UFUNCTION(BlueprintCallable)
	void SetFractalLacunarity(float InLacunarity);

	UFUNCTION(BlueprintCallable)
	void SetFractalGain(float InGain);

	UFUNCTION(BlueprintCallable)
	void SetFractalWeightedStrength(float InWeightedStrength);

	UFUNCTION(BlueprintCallable)
	void SetFractalPingPongStrength(float InPingPongStrength);

	UFUNCTION(BlueprintCallable)
	void SetCellularDistanceFunction(EFastNoiseLiteCellularDistanceFunction InCellularDistanceFunction);

	UFUNCTION(BlueprintCallable)
	void SetCellularReturnType(EFastNoiseLiteCellularReturnType InCellularReturnType);

	UFUNCTION(BlueprintCallable)
	void SetCellularJitter(float InJitter);

	UFUNCTION(BlueprintCallable)
	void SetDomainWarpType(EFastNoiseLiteDomainWarpType InDomainWarpType);

	UFUNCTION(BlueprintCallable)
	void SetDomainWarpAmp(float InAmp);

	UFUNCTION(BlueprintCallable)
	float GetNoise2D(float X, float Y);

	UFUNCTION(BlueprintCallable)
	float GetNoise3D(float X, float Y, float Z);

	UFUNCTION(BlueprintCallable)
	void DomainWarp2D(UPARAM(ref) float& X, UPARAM(ref) float& Y);
	
	UFUNCTION(BlueprintCallable)
	void DomainWarp3D(UPARAM(ref) float& X, UPARAM(ref) float& Y, UPARAM(ref) float& Z);

	// UObject interface
	void PostInitProperties() override;
	void PostLoad() override;
	#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif
	// End UObject interface

private:

	void SetAllNoiseProperties();
	
	UPROPERTY(EditAnywhere)
	int32 Seed = 1337;

	UPROPERTY(EditAnywhere)
	float Frequency = 0.01f;

	UPROPERTY(EditAnywhere)
	EFastNoiseLiteNoiseType NoiseType = EFastNoiseLiteNoiseType::NoiseType_OpenSimplex2;

	UPROPERTY(EditAnywhere)
	EFastNoiseLiteRotationType3D RotationType3D = EFastNoiseLiteRotationType3D::RotationType3D_None;

	UPROPERTY(EditAnywhere)
	int32 Octaves = 3;

	UPROPERTY(EditAnywhere)
	EFastNoiseLiteFractalType FractalType = EFastNoiseLiteFractalType::FractalType_None;

	UPROPERTY(EditAnywhere)
	float FractalLacunarity = 2.0f;

	UPROPERTY(EditAnywhere)
	float FractalGain = 0.5f;

	UPROPERTY(EditAnywhere)
	float FractalWeightedStrength = 0.5f;

	UPROPERTY(EditAnywhere)
	float FractalPingPongStrength = 2.0f;

	UPROPERTY(EditAnywhere)
	EFastNoiseLiteCellularDistanceFunction CellularDistanceFunction = EFastNoiseLiteCellularDistanceFunction::CellularDistanceFunction_Euclidean;

	UPROPERTY(EditAnywhere)
	EFastNoiseLiteCellularReturnType CellularReturnType = EFastNoiseLiteCellularReturnType::CellularReturnType_CellValue;

	UPROPERTY(EditAnywhere)
	float CellularJitter = 0.45f;

	UPROPERTY(EditAnywhere)
	EFastNoiseLiteDomainWarpType DomainWarpType = EFastNoiseLiteDomainWarpType::DomainWarpType_OpenSimplex2;

	UPROPERTY(EditAnywhere)
	float DomainWarpAmp = 1.0f;

	// The actual Noise implementation.
	TSharedPtr<class FastNoiseLite> Noise;
};
