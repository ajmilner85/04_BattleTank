// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

// Holds properties and methods of Tank Barrel
UCLASS(ClassGroup = (Setup), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement, +1 is max upward movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5; // TODO set sensible default
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 14; // TODO set sensible default
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDepressionDegrees = 0; // TODO set sensible default
	
};
