#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

int random(int, int);

class Dice{
public:
    int faces;
    int* numbers;

public:
    Dice(){
       faces = 6;
       _init();
    }

    int getFaces(){
        return faces;
    }

    void setNumbers(int* numbers){
        this->numbers = numbers;
    }

    int* getNumbers(){
        return numbers;
    }

    int roll(){
        return numbers[random(0, faces)];
    }

protected:
    void _init(){
        srand(time(0));
        numbers = new int[faces];
        for(int i = 0 ; i < faces ; i++){
            numbers[i] = i + 1;
        }
    }
};

class Tetrahedron : public Dice{
public:
    Tetrahedron(){
        faces = 4;
        _init();
    }
};

class Octahedron : public Dice{
public:
    Octahedron(){
        faces = 8;
        _init();
    }
};

class Dodecahedron : public Dice{
public:
    Dodecahedron(){
        faces = 12;
        _init();
    }
};

class Icosahedron : public Dice{
public:
    Icosahedron(){
        faces = 20;
        _init();
    }
};

int random(int a, int b){
    return rand() % (b-a) + a;
}

int main(){
    Dice dice = Tetrahedron();
    cout<<dice.faces<<endl;
    for(int i = 0 ; i < 10 ; i++){
        cout<<dice.roll()<<endl;
    }
    cout<<endl;
    int numbers[4] = {1, 3, 5, 7};
    dice.setNumbers(numbers);
    for(int i = 0 ; i < 10 ; i++){
        cout<<dice.roll()<<endl;
    }
}
