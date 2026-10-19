#ifndef CLION_PINCEAU_H
#define CLION_PINCEAU_H
#include <map>
#include <set>
#include <vector>

class Pinceau {

public:

	//static void sphereFunction(std::map<std::vector<int>, double>& _chunk, double _surfaceLevel, bool _isRemoving, int x, int y, int z);
	//static void cubeFunction(std::map<std::vector<int>, double>& _chunk, double _surfaceLevel, bool _isRemoving, int x, int y, int z);
	static inline int radius = 5;

	static std::vector<int> crossingChunk(int p, int sizeChunk, int sizeLnd);

	static std::set<int> sphereBrush(std::vector<std::map<std::vector<int>, double>>& _landscape, double _surfaceLevel, bool _isRemoving, int xW, int yW, int zW, int sizeChunk, int sizeLnd);

	static double distance(std::vector<int> _vec1, std::vector<int> _vec2);

};


#endif //CLION_PINCEAU_H
