// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// void APlayerPawn::Brush(std::vector<std::map<std::vector<int>, double>>& _landscape, double _surfaceLevel,
// 	bool _isRemoving, int xW, int yW, int zW, int sizeChunk, int sizeLnd)
// {
// 	Pinceau::sphereBrush(_landscape, _surfaceLevel,
// 						  _isRemoving, xW, yW, zW, sizeChunk, sizeLnd);
// }

