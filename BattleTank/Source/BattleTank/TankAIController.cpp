// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		// TODO Move toward the player

		// Aim at the player
		//GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire if ready
	}
}

void ATankAIController::BeginPlay()
{
	// Makes parent classes execute their behavior also
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("TankPayerController BeginPlay()"))

	GetControlledTank();
	GetPlayerTank();
}

ATank* ATankAIController::GetControlledTank() const
{
	// Test if player controller is posessing a tank
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank) {
		//UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
		return nullptr;
	}
	//UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *ControlledTank->GetName());
	return ControlledTank;
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) {
		//UE_LOG(LogTemp, Warning, TEXT("AIController found no player controlled tank"));
		return nullptr;
	}
	//UE_LOG(LogTemp, Warning, TEXT("AIController found player controlled tank %s"), *PlayerTank->GetName());
	return PlayerTank;
}