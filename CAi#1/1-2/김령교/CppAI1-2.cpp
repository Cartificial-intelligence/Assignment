//
// Created by 김령교 on 7/9/23.
//
#include <iostream>
#include <random>

using namespace std;
class Dice{
    // 시드(seed) 설정
    int faceCount = 6;

public:
    int roll() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, faceCount);
        return dis(gen);
    }
};


class Tetrahedron: public Dice{
    int faceCount = 4;
};

class Octahedron: public Dice{
    int faceCount = 8;
};

class Dodecahedron: public Dice{
    int faceCount = 12;
};

class Icosahedron: public Dice{
    int faceCount = 20;
};

int main(){
    int hexa = Dice().roll();
    int tetra = Tetrahedron().roll();
    int octa = Octahedron().roll();
    int dodeca = Dodecahedron().roll();
    int icosa = Icosahedron().roll();

    cout << tetra + hexa + octa + dodeca + icosa << endl;
    return 0;
}