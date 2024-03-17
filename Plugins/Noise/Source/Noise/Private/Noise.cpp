#include "Noise.h"

#include "IncludeFastNoiseLite.h"

UNoise::UNoise()
	: Noise{MakeShared<FastNoiseLite>()}
{
}

void UNoise::PostInitProperties()
{
	Super::PostInitProperties();

	SetAllNoiseProperties();
}

void UNoise::PostLoad()
{
	UObject::PostLoad();

	SetAllNoiseProperties();
}

float UNoise::GetNoise2D(float X, float Y)
{
	return Noise->GetNoise(X, Y);
}

float UNoise::GetNoise3D(float X, float Y, float Z)
{
	return Noise->GetNoise(X, Y, Z);
}

#if WITH_EDITOR
void UNoise::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);

	SetAllNoiseProperties();
}
#endif

void UNoise::SetAllNoiseProperties()
{
	Noise->SetSeed(Seed);
	Noise->SetFrequency(Frequency);
	Noise->SetNoiseType(static_cast<FastNoiseLite::NoiseType>(NoiseType));
	Noise->SetRotationType3D(static_cast<FastNoiseLite::RotationType3D>(RotationType3D));
	Noise->SetFractalOctaves(Octaves);
	Noise->SetFractalType(static_cast<FastNoiseLite::FractalType>(FractalType));
	Noise->SetFractalLacunarity(FractalLacunarity);
	Noise->SetFractalGain(FractalGain);
	Noise->SetFractalWeightedStrength(FractalWeightedStrength);
	Noise->SetFractalPingPongStrength(FractalPingPongStrength);
	Noise->SetCellularDistanceFunction(static_cast<FastNoiseLite::CellularDistanceFunction>(CellularDistanceFunction));
	Noise->SetCellularReturnType(static_cast<FastNoiseLite::CellularReturnType>(CellularReturnType));
	Noise->SetCellularJitter(CellularJitter);
	Noise->SetDomainWarpType(static_cast<FastNoiseLite::DomainWarpType>(DomainWarpType));
	Noise->SetDomainWarpAmp(DomainWarpAmp);
}

void UNoise::SetSeed(int32 InSeed)
{
	Seed = InSeed;
	Noise->SetSeed(InSeed);
}
void UNoise::SetFrequency(float InFrequency)
{
	Frequency = InFrequency;
	Noise->SetFrequency(InFrequency);
}

void UNoise::SetNoiseType(EFastNoiseLiteNoiseType InNoiseType)
{
	NoiseType = InNoiseType;
	Noise->SetNoiseType(static_cast<FastNoiseLite::NoiseType>(InNoiseType));
}

void UNoise::SetRotationType3D(EFastNoiseLiteRotationType3D InRotationType3D)
{
	RotationType3D = InRotationType3D;
	Noise->SetRotationType3D(static_cast<FastNoiseLite::RotationType3D>(InRotationType3D));
}

void UNoise::SetFractalOctaves(int32 InOctaves)
{
	Octaves = InOctaves;
	Noise->SetFractalOctaves(InOctaves);
}

void UNoise::SetFractalType(EFastNoiseLiteFractalType InFractalType)
{
	FractalType = InFractalType;
	Noise->SetFractalType(static_cast<FastNoiseLite::FractalType>(InFractalType));
}

void UNoise::SetFractalLacunarity(float InLacunarity)
{
	FractalLacunarity = InLacunarity;
	Noise->SetFractalLacunarity(InLacunarity);
}

void UNoise::SetFractalGain(float InGain)
{
	FractalGain = InGain;
	Noise->SetFractalGain(InGain);
}

void UNoise::SetFractalWeightedStrength(float InWeightedStrength)
{
	FractalWeightedStrength = InWeightedStrength;
	Noise->SetFractalWeightedStrength(InWeightedStrength);
}

void UNoise::SetFractalPingPongStrength(float InPingPongStrength)
{
	FractalPingPongStrength = InPingPongStrength;
	Noise->SetFractalPingPongStrength(InPingPongStrength);
}

void UNoise::SetCellularDistanceFunction(EFastNoiseLiteCellularDistanceFunction InCellularDistanceFunction)
{
	CellularDistanceFunction = InCellularDistanceFunction;
	Noise->SetCellularDistanceFunction(static_cast<FastNoiseLite::CellularDistanceFunction>(InCellularDistanceFunction));
}

void UNoise::SetCellularReturnType(EFastNoiseLiteCellularReturnType InCellularReturnType)
{
	CellularReturnType = InCellularReturnType;
	Noise->SetCellularReturnType(static_cast<FastNoiseLite::CellularReturnType>(InCellularReturnType));
}

void UNoise::SetCellularJitter(float InJitter)
{
	CellularJitter = InJitter;
	Noise->SetCellularJitter(InJitter);
}

void UNoise::SetDomainWarpType(EFastNoiseLiteDomainWarpType InDomainWarpType)
{
	DomainWarpType = InDomainWarpType;
	Noise->SetDomainWarpType(static_cast<FastNoiseLite::DomainWarpType>(InDomainWarpType));
}

void UNoise::SetDomainWarpAmp(float InAmp)
{
	DomainWarpAmp = InAmp;
	Noise->SetDomainWarpAmp(InAmp);
}

void UNoise::DomainWarp2D(float& X, float& Y)
{
	Noise->DomainWarp(X, Y);
}
void UNoise::DomainWarp3D(float& X, float& Y, float& Z)
{
	Noise->DomainWarp(X, Y, Z);
}
