#include <iostream>
#include <cstdlib>
using namespace std;

class dice {
public:
    int face;

    void setFace(int n) {
        this->face = n;
    }

    int roll() {
        return rand() % face;
    }
};

class fourDice: public dice {
public:
    fourDice() {
        dice::setFace(4);
    }

    int roll() {
        return dice::roll();
    }
};

class sixDice: public dice {
public:
    sixDice() {
        dice::setFace(6);
    }

    int roll() {
        return dice::roll();
    }
};

int main() {
    srand(32323);
    sixDice s = sixDice();
    fourDice f = fourDice();

    int temp;
    cout << "반복횟수: " << endl;
    cin >> temp;

    for (int i = 0; i < temp; i++)
    {
        cout << s.roll() + f.roll() << endl;
    }
    

    return 0;
}