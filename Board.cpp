#include <iostream>
#include "Board.h"
#include <fstream>

using namespace std;

//created by GUZEL MUSINA:
//clear the current board, so we can start a new game
//we call this method when we create a new board by constructor
void Board::clear(){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			board[i][j] = '.';
		}
	}
	count = 0;
}

//created by GUZEL MUSINA:
//constructor . Create a new empty board
Board::Board(){
	clear();
}

//created by GUZEL MUSINA:
//print current board
void Board::print(){

    cout <<"   ";
    //print 0 1 2 3  . . .N-1
	for (int i = 0 ; i < N; i++){
		string s = i < 10?"  ":" ";
          cout << i <<s;
	}
	cout <<endl;

	//0 . . . . N-1
	//1 . . . . N-1
	//.
	//.
	//N-1 . . . N-1
	for (int i = 0; i < N; i++){
		string s = i < 10?"  ":" ";
		cout << i<<s;
		for (int j = 0; j < N; j++){
			cout << board[i][j]<<"  ";
		}
		cout <<i;
		cout <<endl<<endl;
	}
	cout <<"   ";
	// print 0 1 2 3 . . . N-1
	for (int i = 0 ; i < N; i++){
		string s = i < 10?"  ":" ";
		cout << i <<s;
	}
	cout <<endl;
}

//created by GUZEL MUSINA:
//check to see the position (x,y) is eligible or not (for both the player and computer)
//use this function in Computer.cpp for evaluation
bool Board::checkEmpty(int x, int y){
    //check that x and y need to be in interval and the board[x][y] must be empty
	if (x >= 0 && x <= N-1 && y >= 0 && y <= N-1 && board[x][y] == '.'){
		return true;
	}
	return false;
}

//created by GUZEL MUSINA:
//put X or O at clear the cell at position (x,y)
void Board::setValue(int x, int y, char c){
	board[x][y] = c;
	if ( c == '.'){
	    //count is the value of "X" and "O" in the board, so when 'c' equal to "."
	    //that means you need to decrease count
		count--;
	}else {
	    //else, we add one more char and count is increase
		count++;
	}
	return;
}

//created by GUZEL MUSINA:
//check if the game is over after the move at position (x,y) or not
bool Board::win(int x, int y){
	return rowOfFive(x,y) || columnOfFive(x,y) || mainDiagnolOfFive(x,y) || reverseDiagnolOfFive(x,y);
}


//created by GUZEL MUSINA:
bool Board::rowOfFive(int x, int y){
	//check for rows
	int temp = 1;
	int i = 1;
	//check from right to left, where x is the same and y is decrease
	//while y is not less than 0 and the pieces are the same
	while (y-i >= 0 && board[x][y-i] == board[x][y]){
		temp++;
		i++;
	}
	i = 1;
	//check from left to right, where x is the same and y is increase
	//while y is not more than N-1 and the pieces are the same
	while (y + i <= N-1 && board[x][y+i] == board[x][y]){
		temp++;
		i++;
	}
	//if temp is equal or bigger than M, it means there are five piece in row
	return (temp >= M);	
}

//created by GUZEL MUSINA:
bool Board::columnOfFive(int x, int y){
	//check for columns
	int temp = 1;
	int i = 1;
    //check from bottom to top, where y is the same and x is decrease
    //while x is not less than 0 and the pieces are the same
	while (x-i >= 0 && board[x-i][y] == board[x][y]){
		temp++;
		i++;
	}
	i = 1;
    //check from top to bottom, where y is the same and x is increase
    //while x is not bigger than N-1 and the pieces are the same
	while (x + i <= N-1 && board[x+i][y] == board[x][y]){
		temp++;
		i++;
	}
    //if temp is equal or bigger than M, it means there are five piece in column
    return (temp >= M);
}

//created by GUZEL MUSINA:
bool Board::mainDiagnolOfFive(int x, int y){
	//check for main diagnol
	int temp = 1;
	int i = 1;
	//from bottom right side to top left side
	while (x-i >= 0 && y - i >= 0 && board[x-i][y-i] == board[x][y]){
		temp++;
		i++;
	}
	i = 1;
	//from top left side to bottom right side
	while (x + i <= N-1 && y + i <= N-1 && board[x+i][y+i] == board[x][y]){
		temp++;
		i++;
	}
    //if temp is equal or bigger than M, it means there are five piece in main diagonal
    return (temp >= M);
}

//created by GUZEL MUSINA:
bool Board::reverseDiagnolOfFive(int x, int y){
	//check for reverse diagnol
	int temp = 1;
	int i = 1;
	//from bottom left side to top right side
	while (x-i >= 0 && y + i <= N-1 && board[x-i][y+i] == board[x][y]){
		temp++;
		i++;
	}
	i = 1;
	//from top right side to bottom left side
	while (x + i <= N-1 && y - i >= 0 && board[x+i][y-i] == board[x][y]){
		temp++;
		i++;
	}
	//if temp is equal or bigger than M, it means there are five piece in reverse diagonal
    return (temp >= M);
}


//created by GUZEL MUSINA:
//determine if the game's result is draw or not.
bool Board::draw(){
	if (count == N*N){
		return true;
	}
	return false;
}


//created by GUZEL MUSINA:
//return value at position (i,j)
char Board::getValue(int i, int j){
	return board[i][j];
}


//created by GUZEL MUSINA:
//return number of cells with placed X or O
int Board::getCount(){
	return count;
}


//created by GUZEL MUSINA:
string Board::toString(){
	string s = "";
	for (int i = 0; i < N; i++){
		for (int j = 0 ; j < N; j++){
			s+= getValue(i, j);
		}
	}
	return s;
}


//created by DANIIL KARPOV:
//has the same algorithm like print() function,
// but write it in file when the game is over.
void Board::printInFile() {
    ofstream out;
    out.open("res.txt");
    if(out.is_open()){
        out << "   " << endl;
        for (int i = 0; i < N; i++) {
            string s = i < 10 ? "  " : " ";
            out << i << s;
        }
        out << endl;
        for (int i = 0; i < N; i++) {
            string s = i < 10 ? "  " : " ";
            out << i << s;
            for (int j = 0; j < N; j++) {
                out << board[i][j] << "  ";
            }
            out << i;
            out << endl << endl;
        }
        out << "   ";
        for (int i = 0; i < N; i++) {
            string s = i < 10 ? "  " : " ";
            out << i << s;
        }
        out << endl;
    }
}

