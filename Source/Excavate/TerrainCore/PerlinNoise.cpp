//
// Created by sushi on 25/09/2026.
//

#include "PerlinNoise.h"

#include <algorithm>
#include <cmath>
#include <random>

std::vector<int> PerlinNoise::permutationTable = {};

PerlinNoise::PerlinNoise() = default;

void PerlinNoise::makePermutationTable(unsigned a) {

    permutationTable.clear();
    for (int i = 0; i < 256; i++) {
        permutationTable.push_back(i);
    }

    std::mt19937 seed(a);

    std::shuffle(permutationTable.begin(), permutationTable.end(), seed);

    std::vector<int> _tempPermutationTable = permutationTable;
    for (auto& i : _tempPermutationTable) {
        permutationTable.push_back(i);
    }
}

double PerlinNoise::makeNoise(double x, double y, double z) {

    double noise;

    //PREPARATIONS COORDONNEES
    // prend le cube qui contient le point (si le point est en x=13.4, il est dans un cube qui se trouve en X=13)
    const int X = static_cast<int>(floor(x)) & 255;
    const int Y = static_cast<int>(floor(y)) & 255;
    const int Z = static_cast<int>(floor(z)) & 255;

    //on transforme les coordonnées 'world' en coordonnées 'relative'
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    //adoucir le perlin
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    //GRADIENTS
    int A = permutationTable[X] + Y; //pré gradient en (x,y,n)
    int B = permutationTable[X+1] + Y; //pré gradient en (x+1,y,n)

    int topLeft = permutationTable[A] + Z; //gradient en (x,y,z)
    int topRight = permutationTable[A+1] + Z; //gradient en (x, y+1, z) car p[A+1] = p[X] + (Y + 1)
    int bottomLeft = permutationTable[B] + Z;
    int bottomRight = permutationTable[B+1] + Z;
    // pour avoir les huits coins il suffit de faire AA+1, BA+1 pour avoir le carré supérieur (= z supérieur)
    //avec ça chaque combinaison de coordonnées donne un résultat unique mais toujours le même entre elles

    //lerp des corners Btm = les 4 coins inférieurs, Top = les 4 coins supérieurs
    double lerpBtmLeft = lerp (u, gradient(permutationTable[topLeft], x, y, z), gradient(permutationTable[bottomLeft], x-1, y, z));
    double lerpBtmRight = lerp(u, gradient(permutationTable[topRight],x,y-1,z), gradient(permutationTable[bottomRight], x-1, y-1, z));

    double lerpTopLeft = lerp (u, gradient(permutationTable[topLeft+1], x, y, z-1), gradient(permutationTable[bottomLeft+1], x-1, y, z-1));
    double lerpTopRight = lerp(u, gradient(permutationTable[topRight+1],x,y-1,z-1), gradient(permutationTable[bottomRight+1], x-1, y-1, z-1));

    noise = lerp(w, lerp (v, lerpBtmLeft, lerpBtmRight), lerp(v, lerpTopLeft, lerpTopRight));

    return noise;
}

//fonction qui calcule "l'adoucissement" du Perlin
double PerlinNoise::fade(double a) {

    return pow(a,3) * (a * (a * 6 - 15 ) +10 ); //formule du fade -> permet d'avoir une dérivée en 0 et 1 = 0 donc de meilleures transitions
}

double PerlinNoise::lerp(double x, double a, double b) {

    return a+ x * (b-a);
    //se place entre a et b selon x -> dans notre cas se placera entre les coins selon le fade des coordonnées
}

double PerlinNoise::gradient(int hash, double x, double y, double z) {
    switch (hash & 15) {
            case 0: return x + y;
            case 1: return -x + y;
            case 2: return x - y;
            case 3: return -x - y;
            case 4: return x + z ;
            case 5: return -x + z ;
            case 6: return x - z ;
            case 7: return -x - z ;
            case 8: return y + z ;
            case 9: return -y + z ;
            case 10: return y - z ;
            case 11: return -y - z ;
            case 12: return y + x ;
            case 13: return -y + z ;
            case 14: return y - x ;
            case 15: return -y - z ;
            default: return 0 ;
    //retourne un produit scalaire par rapport au vecteur partant du centre du cube (qui ont des valeur (1,1,0) ou (1,0,-1)
    //le produit scalaire de u(x,y,z) et v(x',y',z') se calcule xx'+yy'+zz' c'est pour ça qu'on obtient des produits scalaires égaux à x+y ou x-z
    }
}
