//
// Created by sushi on 28/09/2026.
//

#include "Pinceau.h"

#include <vector>
#include <random>
#include <algorithm>
#include <set>

#include "MarchingCubes.h"


static int reach = Pinceau::radius + 1;

/* void Pinceau::sphereFunction(std::map<std::vector<int>, double>& _chunk, double _surfaceLevel, bool _isRemoving, int x, int y, int z) {
    unsigned a = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(a);

    auto it = _chunk.begin();
    std::advance(it, mt() % _chunk.size());

    int x = it->first[0];
    int y = it->first[1];
    int z = it->first[2];

    std::vector<int> _tempPoint = {x, y, z};
    for (int i = -reach; i < reach; i++) {
        for (int j = -reach; j < reach; j++) {
            for (int k = -reach; k < reach; k++) {
                _tempPoint = {x+i, y+j, z+k};
                if (distance(_tempPoint, {x,y,z}) > reach) {
                    continue;
                    }
                if (_chunk.find(_tempPoint) == _chunk.end()) {
                    continue;
                }
                double _hole = _isRemoving ? _surfaceLevel + ((radius - distance(_tempPoint, {x,y,z})) * 0.5) : _surfaceLevel - ((radius - distance(_tempPoint, {x,y,z})) * 0.5) ;
                _chunk[_tempPoint] = _isRemoving ? std::max(_chunk[_tempPoint],_hole) : std::min(_chunk[_tempPoint], _hole);
            }
        }
    }
}

void Pinceau::cubeFunction(std::map<std::vector<int>, double> &_chunk, double _surfaceLevel, bool _isRemoving, int x,
    int y, int z) {

    std::vector<int> _tempPoint = {x, y, z};
    for (int i = -reach; i < reach; i++) {
        for (int j = -reach; j < reach; j++) {
            for (int k = -reach; k < reach; k++) {
                _tempPoint = {x+i, y+j, z+k};
                if (_chunk.find(_tempPoint) == _chunk.end()) {
                    continue;
                }
                double _hole = _isRemoving ? _surfaceLevel + (radius - (radius - x)*(radius-y)*(radius-z) * 0.5) : _surfaceLevel - (radius - (radius - x)*(radius-y)*(radius-z) * 0.5) ;
                _chunk[_tempPoint] = _isRemoving ? std::max(_chunk[_tempPoint],_hole) : std::min(_chunk[_tempPoint], _hole);
            }
        }
    }

}*/

std::vector<int> Pinceau::crossingChunk(int p, int sizeChunk, int sizeLnd) {

    std::vector<int> result;
    if (p<0) return result; // coordonnées hors du chunk
    int c = p / sizeChunk;
    if (c < sizeLnd) result.push_back(c);
    if (p % sizeChunk == 0 && c-1 >=0) result.push_back(c-1); // si p % sizeChunk == 0 ça appartient au chunk d'avant et on check si le chunk d'avant existe
    return result;

    //retourne tous les chunks touchés par un point

}

std::set<int> Pinceau::sphereBrush(std::vector<std::map<std::vector<int>, double>> &_landscape, double _surfaceLevel,
                          bool _isRemoving, int xW, int yW, int zW, int sizeChunk, int sizeLnd)
{
    std::vector _tempPoint = {xW, yW, zW};
    std::set<int> _touchedChunks;

    for (int i = -reach; i <= reach; i++) {
        for (int j = -reach; j <= reach; j++) {
            for (int k = -reach; k <= reach; k++) {
                
                _tempPoint = {xW+i, yW+j, zW+k};
                double d = distance(_tempPoint, {xW,yW,zW});

                if (d > reach) continue;
                
                double _hole = _isRemoving ? _surfaceLevel + (radius -d) * 0.5 : _surfaceLevel - (radius - d) * 0.5; //pour avoir un gradient

                //pour chaque point on check tous les chunks touchés
                for (int cx : crossingChunk(_tempPoint[0], sizeChunk, sizeLnd)) {
                    for (int cy : crossingChunk(_tempPoint[1], sizeChunk, sizeLnd)) {
                        for (int cz : crossingChunk(_tempPoint[2], sizeChunk, sizeLnd)) {

                            int index = cx * sizeLnd * sizeLnd + cy * sizeLnd + cz;
                            
                            auto it = _landscape[index].find(_tempPoint);
                            if (it == _landscape[index].end()) continue;

                            it->second = _isRemoving ? std::max(it->second, _hole) : std::min(it->second, _hole);
                            _touchedChunks.insert(index);

                        }
                    }
                }
            }
        }
    }

    return _touchedChunks;
}

double Pinceau::distance(std::vector<int> _vec1, std::vector<int> _vec2) {

    double dist = 0;
    int distX = _vec1[0] - _vec2[0];
    int distY = _vec1[1] - _vec2[1];
    int distZ = _vec1[2] - _vec2[2];
    dist = sqrt((distX*distX)+(distY*distY)+(distZ*distZ));

    return dist;
}
