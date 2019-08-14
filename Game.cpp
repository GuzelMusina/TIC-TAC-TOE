
#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Computer.h"
#include <vector>

//Mu Jia:
//this two libraries for grapics
#include <stdio.h>
#include <windows.h>

using namespace std;

//Mu Jia:
//create an enumerator of console colors
enum ConsoleColor {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};




//create new game. A game can include many rounds if the player wants to play again
Game::Game() {
    board.clear();
}

//CREATED BY VADIM IVANAEVSKII(functionality) AND GUZEL MUSINA(interface)
//play the game in console. Here is the structure of how the game is played
void Game::playConsole() {
    board.clear(); //clear board here
    Computer computer;
    bool flag = true; //flag is our game is played
    int current = 1;
    int x = -1, y = -1;
    vector<int> v;
    int playerChoice;
    int gameType;

    //Retrieves a handle to the specified standard device (standard input, standard output, or standard error).
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
/*
 * 0 = Black 8 = Gray
1 = Blue 9 = Light Blue
2 = Green A = Light Green
3 = Aqua B = Light Aqua
4 = Red C = Light Red
5 = Purple D = Light Purple
6 = Yellow E = Light Yellow
7 = White F = Bright White
 */
    //set all system colors that the background will be LightPurple
    // and the text will be Bright White
    system("color DF");

    //choose mode of game
    cout << "Player mode = 1, computer mode = 2" << endl;
    //set for input their special color, use enum value for it
    //Yellow - color of background, Magenta - color of text
    SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
    cin >> gameType;

    while (gameType != 1 && gameType != 2) {
        system("color DF");
        cout << "Incorrect choice! Enter your choice again. " << endl;
        cout << "Player mode = 1, computer mode = 2" << endl;
        SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
        cin >> playerChoice;
        if (playerChoice == 1 || playerChoice == 2) break;
    }

    //computer mode
    if (gameType == 2) {
        system("color DF");
        cout << "Please choose 'X' or 'O' to play.\nEnter 1 to choose 'X', 2 to choose 'O': " << endl;
        SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
        cin >> playerChoice;
        while (playerChoice != 1 && playerChoice != 2) {
            system("color DF");
            cout << "Incorrect choice! Enter your choice again. " << endl;
            cout << "Enter 1 to choose 'X', 2 to choose 'O': " << endl;
            SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
            cin >> playerChoice;
            if (playerChoice == 1 || playerChoice == 2) break;
        }

        //set symbols
        if (playerChoice == 1) {
            board.setPlayerSymbol('X');
            board.setComputerSymbol('O');
        } else {
            board.setPlayerSymbol('O');
            board.setComputerSymbol('X');
        }
        //option for player to go first
        system("color DF");
        cout << "You play as " << board.getPlayerSymbol() << ". Let's start!" << endl;
        cout << "Do you want to go first? y/n" << endl;
        char playerGoFirst;
        SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));

        cin >> playerGoFirst;

        system("color DF");
        if (playerGoFirst == 'Y' || playerGoFirst == 'y') {
            current = 1;
            cout << "OK. You go first!" << endl;
        } else {
            cout << "OK. I go first!" << endl;
            current = 2;
        }

        board.print(); //print our board
        while (flag) {
            cout << endl;
            if (current == 1) {
                //get player move
                system("color DF");
                cout << "Your turn. (" << getCurrentSymbol(current) << " )" << endl;
                cout << "Enter X coordinate of your move: ";
                SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
                cin >> x;
                system("color DF");
                cout << "Enter Y coordinate of your move: ";
                SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
                cin >> y;
            } else {
                // get computer move
                v = computer.nextMoveAlphaBeta(board);
                x = v[0];
                y = v[1];

            }

            //check if the move is legit or not
            if (!board.checkEmpty(x, y)) {
                system("color DF");
                cout << endl << "Not a legal move. Try again!" << endl;
                continue; //if not, continue the loop
            } else {
                //if the move is legit, update the board
                board.setValue(x, y, getCurrentSymbol(current));
                board.print();
                system("color DF");
                if (current == 1) {
                    cout << "Your move is : (" << x << ", " << y << ") " << endl;
                } else {
                    cout << "My move is : (" << x << ", " << y << ") " << endl;
                }
            }

            //check if the game is over or not
            if (board.win(x, y)) {
                board.print();
                system("color DF");
                if (current == 1) {
                    cout << "CONGRATULATIONS! YOU WON!" << endl;
                } else {
                    cout << "I WON!!!" << endl;
                }
                break;
            } else if (board.draw()) {
                board.print();
                system("color DF");
                cout << "Draw game!" << endl;
                break;
            } else { // if the game is not over, change current player between the player and the computer
                current = 3 - current;
            }
        }
        //if is it player to player mode then 90% of functionality is the same but without computer
    } else if (gameType == 1) {
        system("color DF");
        cout << "Please choose 'X' or 'O' to play.\nEnter 1 to choose 'X', 2 to choose 'O': " << endl;
        SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
        cin >> playerChoice;
        while (playerChoice != 1 && playerChoice != 2) {
            system("color DF");
            cout << "Incorrect choice! Enter your choice again. " << endl;
            cout << "Enter 1 to choose 'X', 2 to choose 'O': " << endl;
            SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
            cin >> playerChoice;
            if (playerChoice == 1 || playerChoice == 2) break;
        }

        if (playerChoice == 1) {
            board.setPlayerSymbol('X');
            board.setComputerSymbol('O');
        } else {
            board.setPlayerSymbol('O');
            board.setComputerSymbol('X');
        }
        system("color DF");
        cout << "p1 play as " << board.getPlayerSymbol() << ". p2 as" << board.getComputerSymbol() << endl;

        cout << "Who go first? 1 for p1, 2 for p2" << endl;
        int playerGoFirst;
        SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
        cin >> playerGoFirst;

        if (playerGoFirst == '1') {
            current = 1;
            system("color DF");
            cout << "OK. p1 go first!" << endl;
        } else {
            system("color DF");
            cout << "OK. p2 go first!" << endl;
            current = 2;
        }

        board.print();
        while (flag) {
            //board.print();
            cout << endl;
            if (current == 1) { //get player move
                system("color DF");
                cout << "Your turn. (" << getCurrentSymbol(current) << " )" << endl;
                cout << "Enter X coordinate of your move: ";
                SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
                cin >> x;
                system("color DF");
                cout << "Enter Y coordinate of your move: ";
                SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
                cin >> y;
            } else if (current == 2) { // get p2 move
                system("color DF");
                cout << "Your turn. (" << getCurrentSymbol(current) << " )" << endl;
                cout << "Enter X coordinate of your move: ";
                SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
                cin >> x;
                system("color DF");
                cout << "Enter Y coordinate of your move: ";
                SetConsoleTextAttribute(hConsole, (WORD) ((Yellow << 4) |  Magenta));
                cin >> y;
            }

            //check if the move is legit or not
            if (!board.checkEmpty(x, y)) {
                system("color DF");
                cout << endl << "Not a legal move. Try again!" << endl;
                continue; //if not, continue the loop
            } else {//if the move is legit, update the board

                board.setValue(x, y, getCurrentSymbol(current));
                board.print();
                system("color DF");
                if (current == 1) {
                    cout << "p1 move is : (" << x << ", " << y << ") " << endl;
                } else {
                    cout << "p2 move is : (" << x << ", " << y << ") " << endl;
                }
            }

            //check if the game is over or not
            if (board.win(x, y)) {
                board.print();
                system("color DF");
                if (current == 1) {
                    cout << "p1 CONGRATULATIONS! YOU WON!" << endl;
                } else {
                    cout << "p2 CONGRATULATIONS! YOU WON!" << endl;
                }
                break;
            } else if (board.draw()) {
                board.print();
                system("color DF");
                cout << "Draw game!" << endl;
                break;
            } else { // if the game is not over, change current player between the player and the computer
                current = 3 - current;
            }
        }

    }
}

//get symbol of the current player
char Game::getCurrentSymbol(int current) {
    if (current == 1) {
        return board.getPlayerSymbol();
    } else {
        return board.getComputerSymbol();
    }
}


//start the game
void Game::run() {
    bool flag = true;
    char x;
    while (flag) {
        playConsole();
        board.printInFile();
        system("color DF");
        cout << "Do you want to play another game? y/n" << endl;
        cin >> x;
        if (x == 'N' || x == 'n') {
            flag = false;
        } else {
            cout << "------------------------------------------------------" << endl;
        }
    }
}



