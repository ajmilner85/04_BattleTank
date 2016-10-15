// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	// Makes parent classes execute their behavior also
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("TankPayerController BeginPlay()"))

	// Test if player controller is posessing a tank
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *ControlledTank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter, as such not initialized
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	UPROPERTY(EditAnywhere)
	double CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	double CrosshairYLocation = 0.3333;

	FVector2D ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation, 
		ViewportSizeY * CrosshairYLocation
	);
	FVector CameraLocation;
	FVector LookDirection;
	// Variables for de-project out parameters

	int32 LineTraceRange = 1000000;
	FHitResult HitResult;
	// De-proect reticule location to a world position/direciton
	if (GetLookDirection(ScreenLocation, CameraLocation, LookDirection))
	{
		// Trace line from camera origin, through HUD reticule location, to world to a maximum range
		GetPawn()->GetWorld()->LineTraceSingleByChannel(
			HitResult,
			CameraLocation,
			CameraLocation + (LookDirection * LineTraceRange),
			ECollisionChannel::ECC_Visibility
			);

		// If collides with world
		if (HitResult.IsValidBlockingHit()) {
			HitLocation = HitResult.Location;
			//double Time = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Warning, TEXT("%f - Have aim solution? True"), Time );
			//UE_LOG(LogTemp, Warning, TEXT("World Collision"));
			return true;
		}
		//double Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f - Have aim solution? False"), Time);
		//UE_LOG(LogTemp, Warning, TEXT("NO World Collision"));
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& CameraLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraLocation,
		LookDirection
	);
	return true;
}