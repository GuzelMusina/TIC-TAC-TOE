
#include <iostream>

#include "Computer.h"
#include "Board.h"
#include <vector>

using namespace std;

//CREATED BY VADIM IVANAEVSKII / gao wei guo
//find next move with the help of alpha-beta
//want to maximize the evaluation function. It's good for the computer
vector<int> Computer::nextMoveAlphaBeta(Board & board){
	vector<int> v = {0,0}; // vector which save coordinates of choice
	int M = INT_MIN, x = -1, y = -1;

	//check every cell
	for (int i = 0; i <= N-1;i++){
		for (int j = 0; j <= N-1; j++){
		    //check if our char is '.' and check cells around
			if (board.getValue(i, j) == '.' && adjacentPlaced(board, i, j) ){
			    // if is it ok, then go the algorithm
				int temp = minimaxAlphaBeta (board, 2, true,INT_MIN, INT_MAX, i, j);
				//check if algorithm works good and knows which way is better, then x = i y = j
				//else if temp = int_min it means that algorithm don't know which way it need to do
				//because player choose the better cell to win
				if (M < temp){
					M = temp;
					x = i;
					y = j;
				}
			}
		}
	}
	//so if computer is first or computer don't know what it need to do, then use it
	if (x == -1 && y == -1){
		x = N/2;
		y = N/2;
	}
	//save coordinates to array and return
	v[0] = x;
	v[1] = y;
	return v;
}



//Created by DANIIL KARPOV
//minimaxAlphaBeta algorithm with alpha-beta to help determine the next move for the computer
//Use evaluation function with depth here.
//higher score is good for computer, lower score is good for player
//isMax = true if the move at (x,y) is of computer
int Computer::minimaxAlphaBeta(Board & board, int depth, bool isMax, int alpha, int beta, int x , int y){
	char c = isMax ?  board.getComputerSymbol()  :  board.getPlayerSymbol(); 
	board.setValue(x,y,c); 
	
	if (board.win(x,y)){
		board.setValue(x,y,'.');	
		if (isMax){//computer wins
			return INT_MAX;
		}else {
			return INT_MIN;// player wins, therefore, need to minimize score so computer will not choose this path
		}
	}else if (board.draw()){
		board.setValue(x,y,'.');	
		return 0;
	}
	if (depth == 0){
		int value = 0;
		if (checkVisitedBoard(board) == true){
			value = getEvaluation(board); // evaluation of board was already stored
		}else{
			value = evaluation(board, isMax); //need to compute evaluation of this new board
			insertToHashMap(board, value); //store evaluation of this new board into memory
		}
		board.setValue(x,y,'.');
		
		//cout <<"evaluation at "<<x <<" "<<y<< " is "<< value <<endl;
		return value;
	}
	
	//save the X positions of available cells into firstCoord, Y positions of available cells into secondCoord
	vector<int> firstCoord;
	vector<int> secondCoord;
	for (int i = 0; i < N; i++){
		for (int j = 0; j<N; j++){
			if (board.getValue(i,j) == '.' && adjacentPlaced(board, i, j)){
				firstCoord.push_back(i);
				secondCoord.push_back(j);
			}
		}
	}
	
	int len = (int) firstCoord.size();
	if (isMax == true){ // try to minimize because now is player's turn
		int m = INT_MAX;
		for (int i = 0; i < len; i++){
			//recursive function to calculate temp
			int temp = minimaxAlphaBeta(board,depth - 1, false, alpha, beta, firstCoord[i], secondCoord[i]);
			if (m > temp){
				m = temp;
			}
			if (beta > m){
				beta = m;
			 }	
			 if (alpha >= beta){
				break;
			 }
		}
		board.setValue(x,y,'.');

		return m;
	}else {//try to maximize
		int M = INT_MIN;
		for (int i = 0; i < len; i++){
			//recursive function to calculate temp
			int temp = minimaxAlphaBeta(board, depth - 1, true, alpha, beta, firstCoord[i], secondCoord[i]);
			if (M < temp){
				M = temp;
			}
			if (alpha < M){
				alpha = M;
			 }
			 if (alpha >= beta){
				break;
			 }
		}
		board.setValue(x,y,'.');

		return M;
	}
}

//CREATED BY VADIM IVANAEVSKII/ gao wei guo
//this function give computer  evaluation which way better or not for every cell
int Computer::evaluation(Board & board, bool isMax){
    //if isMax is true, computer is about to make the move at (x,y)
	int sum = 0;
	vector<int> computerPattern(M+1,0); //storage of computer evaluations
	vector<int> playerPattern(M+1,0); // storage of player evaluations

	//check every cell
	for (int  i = 0 ; i < N; i++){
		for (int j = 0; j < N ; j++){
		    //if this cell X or Y for do some work or we don't need it to do
			if (board.getValue(i,j) != '.'){
				
				//count patterns in columns
				char c = board.getValue(i,j);
				//bool variable is it computer symbol or not
				bool needMax = c == board.getComputerSymbol();

				//check symbols to the top and to the bottom
				int sameSymbol = 1; // count same symbols in columns 
				int k = 1;
				while (i- k >= 0 && board.getValue(i-k, j)  == c){
					sameSymbol++;
					k++;
				}

				//consider value at i - k later to see if it's blocked or not
				int l = 1;
				while (i + l <= N-1 && board.getValue(i+l, j) == c){
					sameSymbol++;
					l++;
				}

				//if same symbols in a column >= 5 then increase counter in this place of array
				if (sameSymbol >= M){
				    //check is it computer symbol or not to understand which array we need
					if (needMax) computerPattern[M]++;
					else playerPattern[M]++;
					//the same check but for 4,3,2,1
				}else if (sameSymbol == M - 1 && (board.checkEmpty(i-k,j) || board.checkEmpty(i+l,j))){ 				
					if (needMax) computerPattern[M-1]++;
					else playerPattern[M-1]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i-k,j) || board.checkEmpty(i+l,j))){
					if (needMax) computerPattern[M-2]++;
					else playerPattern[M-2]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i-k,j) && board.checkEmpty(i+l,j))){
					if (needMax) computerPattern[M-3]++;
					else playerPattern[M-3]++;
				}else if (sameSymbol == M - 3 && board.checkEmpty(i-k,j) && board.checkEmpty(i+l,j)){
					if (needMax) computerPattern[M-4]++;
					else playerPattern[M-4]++;
				}
				
				
				//-------------------------------------------------------------------------------
				sameSymbol = 1; // count same symbols in rows
				k = 1;

				//the same work but for a row
				while (j - k >= 0 && board.getValue(i, j-k)  == c){
					sameSymbol++;
					k++;
				}
				
				
				//consider value at i - k later to see if it's blocked or not
				l = 1;
				while (j + l <= N-1 && board.getValue(i, j+l) == c){
					sameSymbol++;
					l++;
				}

				//also like for a columns add to arrays, but it work for a row
				if (sameSymbol >= M){
					if (needMax) computerPattern[M]++;
					else playerPattern[M]++;
				}else if (sameSymbol == M - 1 && (board.checkEmpty(i,j-k) || board.checkEmpty(i,j+l))){ 				
					if (needMax) computerPattern[M-1]++;
					else playerPattern[M-1]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i,j-k) || board.checkEmpty(i,j+l))){
					if (needMax) computerPattern[M-2]++;
					else playerPattern[M-2]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i,j-k) && board.checkEmpty(i,j+l))){
					if (needMax) computerPattern[M-3]++;
					else playerPattern[M-3]++;
				}else if (sameSymbol == M - 3 && board.checkEmpty(i,j-k) && board.checkEmpty(i,j+l)){
					if (needMax) computerPattern[M-4]++;
					else playerPattern[M-4]++;
				}
				
				//--------------------------------------------------------------
				
				sameSymbol = 1;// count same symbols in main diagonal
				k = 1;
				//the same work but for diagonals
				while (i - k >= 0 && j - k >= 0 && board.getValue(i-k, j- k)  == c){
					sameSymbol++;
					k++;
				}
				
				
				//consider value at i - k later to see if it's blocked or not
				l = 1;
				while (i + l <= N-1 && j + l <= N-1 && board.getValue(i+l, j+l ) == c){
					sameSymbol++;
					l++;
				}

				if (sameSymbol >= M){
					if (needMax) computerPattern[M]++;
					else playerPattern[M]++;
				}else if (sameSymbol == M - 1 && (board.checkEmpty(i-k,j-k) || board.checkEmpty(i+l,j+l))){ 				
					if (needMax) computerPattern[M-1]++;
					else playerPattern[M-1]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i-k,j-k) || board.checkEmpty(i+l,j+l))){
					if (needMax) computerPattern[M-2]++;
					else playerPattern[M-2]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i-k,j-k) && board.checkEmpty(i+l,j+l))){
					if (needMax) computerPattern[M-3]++;
					else playerPattern[M-3]++;
				}else if (sameSymbol == M - 3 && board.checkEmpty(i-k,j-k) && board.checkEmpty(i+l,j+l)){
					if (needMax) computerPattern[M-4]++;
					else playerPattern[M-4]++;
				}
				
				
				
				//-----------------------------------------------------------------------
				
				
				sameSymbol = 1;// count same symbols in reverse diagnols
				k = 1;
				//for reverse diagonals
				while (i - k >= 0 && j + k <= N-1 && board.getValue(i-k, j+ k)  == c){
					sameSymbol++;
					k++;
				}
				
				
				//consider value at i - k later to see if it's blocked or not
				l = 1;
				while (i + l <= N-1 && j - l >= 0 && board.getValue(i+l, j-l ) == c){
					sameSymbol++;
					l++;
				}

				if (sameSymbol >= M){
					if (needMax) computerPattern[M]++;
					else playerPattern[M]++;
				}else if (sameSymbol == M - 1 && (board.checkEmpty(i-k,j+k) || board.checkEmpty(i+l,j-l))){ 				
					if (needMax) computerPattern[M-1]++;
					else playerPattern[M-1]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i-k,j+k) || board.checkEmpty(i+l,j-l))){
					if (needMax) computerPattern[M-2]++;
					else playerPattern[M-2]++;
				}else if (sameSymbol == M - 2 && (board.checkEmpty(i-k,j+k) && board.checkEmpty(i+l,j-l))){
					if (needMax) computerPattern[M-3]++;
					else playerPattern[M-3]++;
				}else if (sameSymbol == M - 3 && board.checkEmpty(i-k,j+k) && board.checkEmpty(i+l,j-l)){
					if (needMax) computerPattern[M-4]++;
					else playerPattern[M-4]++;
				}
				
				
			}	
		}
	}
	//check if we have at least 1 line with 5 or more the same symbols for computer
	if (computerPattern[M] > 0) return INT_MAX;
	//or for player
	if (playerPattern[M] > 0) return INT_MIN;

	//if we have not it, then need to calculate value for priorities in future
	int x = 1;
	sum += computerPattern[1];
	sum -= playerPattern[1]*5;
	for (int i = 2 ; i < M ; i++){
		//cout <<computerPattern[i] << " : "<<playerPattern[i]<<endl;
		x *= 100;
		sum += computerPattern[i] * x;
		sum -= playerPattern[i] * x * 10;
	}	
	return sum;
}



//Created by DANIIL KARPOV
//Checking area near cell and return true if find character
bool Computer::adjacentPlaced(Board & board , int x, int y){

	bool value = false;
	if (board.getValue(x,y) != '.') return false;
	//. . .
	//. C .
	//. . .
	//checking area near C
	vector<vector<int>> adjacent = {{-1,-1},{-1,0}, {-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1}};
	for (auto d:adjacent){
		//checking nearby area
		//it shouldn't be out of border
		if (x+d[0] >=0 && y+d[1]>=0 && x+d[0] <= N-1 && y + d[1] <= N-1){
			value = value || (board.getValue(x+d[0],y+d[1]) != '.');
		}
	}
	return value;
}



//Created by DANIIL KARPOV
//check if the evaluation function of a particular board is already in the memory or not
bool Computer::checkVisitedBoard(Board & board){
	string s = board.toString();
	if (hashMap.find(s) != hashMap.end()){
		return true;
	}
	return false;
}

//CREATED BY VADIM IVANAEVSKII/ gao wei guo
//if the evaluation function of a board is already in the memory, just need to take it out.
// this will save time computing the evaluation function of the board.
int Computer::getEvaluation(Board & board){
	if (checkVisitedBoard(board)){
		return hashMap[board.toString()]; 
	}
	return -1;
}


//insert values to hash map

void Computer::insertToHashMap(Board & board, int eval){
	string s = board.toString();
	hashMap[s] = eval;
	return;
}






