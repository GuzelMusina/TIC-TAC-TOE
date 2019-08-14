#ifndef __Gomoku__Board__
#define __Gomoku__Board__

#include <stdio.h>

using namespace std;

//board size
const int N = 11;
//how many piece for win
const int M = 5;

//created by GUZEL MUSINA
class Board {
private:
    char board[N][N];
    char playerSymbol;
    char playerSymbol2;
    char computerSymbol;
    //Mu Jia:
    //count how many "X" and "O" in chess
    int count;
public:
    Board();

    void clear();

    void print();

    void printInFile();

    bool checkEmpty(int, int);

    bool win(int, int);

    bool draw();

    char getValue(int, int);

    void setValue(int, int, char);

    int getCount();

    //return player symbol it can be "X" or "O"
    char getPlayerSymbol() {
        return playerSymbol;
    }

    //return computer symbol it can be "X" or "O"
    char getComputerSymbol() {
        return computerSymbol;
    }

    //change the player symbol it can be "X" or "O"
    void setPlayerSymbol(char c) {
        playerSymbol = c;
    }

    //change the computer symbol it can be "X" or "O"
    void setComputerSymbol(char c) {
        computerSymbol = c;
    }

    bool rowOfFive(int, int);

    bool columnOfFive(int, int);

    bool mainDiagnolOfFive(int, int);

    bool reverseDiagnolOfFive(int, int);

    string toString();

};

#endif /* defined(__Gomoku__Board__) */
