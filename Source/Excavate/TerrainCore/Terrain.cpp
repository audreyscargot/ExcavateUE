#include "Terrain.h"

#include <iostream>
#include "PerlinNoise.h"

int TerrainCore::Terrain::chunkSize = 16;

std::map<std::vector<int>, double> TerrainCore::Terrain::createChunk(int _chunkSize, int xW, int yW, int zW) {

    std::map<std::vector<int>, double> _chunkPoints;
    for (int x = 0; x < _chunkSize+1; x++) {
        for (int y = 0; y < _chunkSize+1; y++) {
            for (int z = 0; z < _chunkSize+1; z++) {
                _chunkPoints.insert(std::pair<std::vector<int>, double>({xW * chunkSize + x, yW * chunkSize + y, zW * chunkSize + z}, 1));
            }
        }
    }
    return _chunkPoints;
}

std::map<std::vector<int>, double> TerrainCore::Terrain::generateChunkNoise(std::map<std::vector<int>, double> _chunk) {

    double min = 0;
    double max = 0;

    for (auto& _point : _chunk) {

        std::vector<int> _pointCoordinate = _point.first;
        _point.second = PerlinNoise::makeNoise(_pointCoordinate[0]*0.05, _pointCoordinate[1]*0.05, _pointCoordinate[2]*0.05);

        if (_point.second < min) min = _point.second;
        if (_point.second > max) max = _point.second;
    }
    return _chunk;
}

std::map<std::vector<int>, double> TerrainCore::Terrain::generateTerrain(int xW, int yW, int zW) {

    std::map<std::vector<int>, double> _chunk = createChunk(chunkSize, xW, yW, zW);
    _chunk = generateChunkNoise(_chunk);
    return _chunk;
}

int TerrainCore::Terrain::GetChunkSize() {
    return chunkSize;
}
