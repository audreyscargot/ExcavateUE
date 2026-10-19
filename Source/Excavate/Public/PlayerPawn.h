// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class EXCAVATE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UFUNCTION(BlueprintCallable)
	// void Brush(std::vector<std::map<std::vector<int>, double>> &_landscape, double _surfaceLevel,
	// 					  bool _isRemoving, int xW, int yW, int zW, int sizeChunk, int sizeLnd);
};
