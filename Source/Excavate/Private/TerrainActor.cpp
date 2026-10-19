// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainActor.h"

#include <set>
#include "ProceduralMeshComponent.h"
#include "Excavate/TerrainCore/Terrain.h"
#include "Excavate/TerrainCore/MarchingCubes.h"
#include "Excavate/TerrainCore/PerlinNoise.h"
#include "Excavate/TerrainCore/Pinceau.h"

// Sets default values
ATerrainActor::ATerrainActor()
{
 	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("TerrainMesh");
	SetRootComponent(Mesh);

}

void ATerrainActor::Paint(FVector _worldLocation, bool _isRemoving)
{
	FVector _local = GetActorTransform().InverseTransformPosition(_worldLocation) / scale;
	int x = FMath::RoundToInt(_local.X);
	int y = FMath::RoundToInt(_local.Y);
	int z = FMath::RoundToInt(_local.Z);
	UE_LOG(LogTemp, Warning, TEXT("PaintTerrain Local XYZ = %d %d %d"), x, y, z);
	if (x < Pinceau::radius || y < Pinceau::radius || z < Pinceau::radius || x > TerrainCore::Terrain::chunkSize*landscapeSize-Pinceau::radius || y > TerrainCore::Terrain::chunkSize*landscapeSize-Pinceau::radius || z > TerrainCore::Terrain::chunkSize*landscapeSize-Pinceau::radius) return;
	std::set<int32> touchedChunks = Pinceau::sphereBrush(Landscape, MarchingCubes::GetSurfaceLevel(), _isRemoving, x,y,z, TerrainCore::Terrain::GetChunkSize(), landscapeSize);
	
	for (int index : touchedChunks)
	{
		RefreshChunk(index);
	}
}

// Called when the game starts or when spawned
void ATerrainActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay terrain"));
	
	// unsigned a = std::chrono::system_clock::now().time_since_epoch().count();
	PerlinNoise::makePermutationTable(12345);
	
	int size = TerrainCore::Terrain::GetChunkSize();

	//on génère les chunks
	for (int i = 0; i < landscapeSize; ++i) {
		for (int j = 0; j < landscapeSize; ++j) {
			for (int k = 0; k < landscapeSize; ++k) {
				auto chunk = TerrainCore::Terrain::generateTerrain(i,j,k);
				
				for (int a = 0; a < size; a++) {
					for (int b = 0; b < size; b++) {
						for (int c = 0; c < size ; c++) {
							MarchingCubes::sampleVertices(chunk, a,b,c,i,j,k, size);
						}
					}
				}
				int32 index = i * landscapeSize * landscapeSize + j * landscapeSize + k;
				SendToMesh(index);
				MarchingCubes::Reset();
				
				Landscape.push_back(std::move(chunk));
			}
		}
	}
	
}

void ATerrainActor::SendToMesh(int32 index)
{
	const auto& _triangles = MarchingCubes::GetTriangles();
	const auto& _normals = MarchingCubes::GetNormals();
	if (_triangles.empty()) return;
	
	TArray<FVector> _vertices;
	TArray<FVector> _norms;
	
	TArray<int> _indices;
	
	for (size_t i = 0; i < _triangles.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			const auto& p = _triangles[i][j];
			const auto& n = _normals[i][j];
			_vertices.Add(FVector(p[0], p[1], p[2]) * scale);
			_norms.Add(FVector(n[0], n[1], n[2]));
		}
	}
	
	for (int i = 0; i < _vertices.Num(); i+=3)
	{
		_indices.Add(i);
		_indices.Add(i+2);
		_indices.Add(i+1);
	}
	
	Mesh->CreateMeshSection(index, _vertices, _indices, _norms, {}, {}, {}, true);
}

void ATerrainActor::RefreshChunk(int32 index)
{
	int size = TerrainCore::Terrain::GetChunkSize();
	int k = index % landscapeSize;
	int j = index / landscapeSize % landscapeSize;
	int i = index / (landscapeSize * landscapeSize);
	
	MarchingCubes::Reset();
	for (int a = 0; a < size; a++)
	{
		for (int b = 0; b < size; b++)
		{
			for (int c = 0; c < size; c++)
			{
				MarchingCubes::sampleVertices(Landscape[index], a,b,c,i,j,k, size);
			}
		}
	}
	
	SendToMesh(index);
	MarchingCubes::Reset();
}

