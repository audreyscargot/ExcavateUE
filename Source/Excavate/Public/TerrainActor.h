// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainActor.generated.h"

class UProceduralMeshComponent;

UCLASS()
class EXCAVATE_API ATerrainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainActor();
	
	std::vector<std::map<std::vector<int>, double>> Landscape;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 landscapeSize = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float scale = 50.f;
	
	UFUNCTION(BlueprintCallable)
	void Paint(FVector _worldLocation, bool _isRemoving);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* Mesh;
	
	void SendToMesh(int32 index);
	
	void RefreshChunk(int32 index);

};
