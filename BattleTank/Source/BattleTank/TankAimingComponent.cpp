// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector LaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ActorsToIgnore = { GetOwner() };

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		LaunchVelocity, // Out parameter
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace, // Paramater must be present to prevent bug
		FCollisionResponseParams(ECollisionResponse::ECR_Block),
		ActorsToIgnore,
		false // Debug lines
	);

	auto Time = GetWorld()->GetTimeSeconds(); // TODO Remove after debugging
	// Calculate the LaunchVelocity
	if (bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
		// UE_LOG(LogTemp, Warning, TEXT("%f - Aim Solution Found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// TODO clean up pseudocode
	// Get current Barrel rotation unit vector z component
	// If barrel unit rotation unit vector z component does not equal the AimDirection unit vector
	// Start moving barrel toward desired elevation at desired speed

	// Ben
	// Work-out difference between current barrel rotation and aim direction

	Barrel->Elevate(5); // TODO remove magic number
}