//
// Created by sushi on 25/09/2026.
//

#ifndef CLION_PERLINNOISE_H
#define CLION_PERLINNOISE_H
#include <vector>


class PerlinNoise {

    public:

    static std::vector<int> permutationTable;

    PerlinNoise();
    static void makePermutationTable(unsigned a);

    static double makeNoise(double x, double y, double z);

    static double fade(double a);

    static double lerp(double x, double a, double b);

    static double gradient(int hashCode, double x, double y, double z);

};


#endif //CLION_PERLINNOISE_H
