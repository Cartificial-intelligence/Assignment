#include <bits/stdc++.h>
using namespace std;

class Dice
{
public:
    int diceNumber;
    int *diceContents;
    Dice(){
    }
    int roll(){
        return diceContents[rand()%diceNumber];
    }
    void setContents(){
        int *a = new int[diceNumber];
        for(int i=0;i<diceNumber;i++){
            int b;
            scanf("%d", &b);
            a[i] = b;
        }
        diceContents = a;
    }
    const int* getContents(){
        return diceContents;
    }
};

class Dice4 : public Dice{
public:
    Dice4(){
        diceNumber = 4;
        printf("Enter %d numbers:",diceNumber);
        setContents();
    }
};
class Dice6 : public Dice{
public:
    Dice6(){
        diceNumber = 6;
        printf("Enter %d numbers:",diceNumber);
        setContents();
    }
};
int main(){
    srand(0);
    Dice4 *dice4 = new Dice4();
    Dice6 *dice6 = new Dice6();
    system("cls");
    printf("Enter Number of Tries\n");
    int tries;
    scanf("%d",&tries);
    for(int i=0;i<tries;i++){
        int tryDice4 = dice4->roll();
        int tryDice6 = dice6->roll();
        printf("Try %d: %d+%d = %d\n",i+1,tryDice4, tryDice6, tryDice4+tryDice6);
    }
}
