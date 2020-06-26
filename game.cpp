#include <iostream>
#include <sstream>
#include <iomanip>
#include "game.h"

using namespace std;

Game::Game() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			board[i][j] = '-';
		}
	}
}

void Game::printBoard(char AIboard[3][3]) {
	cout << "-------------------";
	for(int i = 0; i < 3; i++) {
		cout << '\n' << "|";
		for(int j = 0; j < 3; j++) {
			cout << setw(3) << AIboard[i][j] << setw(3) << " |";
		}
	}
	cout << '\n' << "-------------------" << '\n';
}

bool Game::gameOver(char AIboard[3][3]) {
	if(checkWin(HUMAN, AIboard)) return true;
	else if(checkWin(AI, AIboard)) return true;

	bool emptySpace = false;
	for(int i = 0; i < 3; i++) {
		if(AIboard[i][0] == '-' || AIboard[i][1] == '-' || AIboard[i][2] == '-')
			emptySpace = true;
	}
	return !emptySpace;
}

bool Game::checkWin(Player player, char AIboard[3][3]) {
	char playerChar;
	if(player == HUMAN) playerChar = human;
	else playerChar = ai;

	for(int i = 0; i < 3; i++) {
		// Check horizontals
		if(AIboard[i][0] == playerChar && AIboard[i][1] == playerChar && AIboard[i][2] == playerChar)
			return true;

		// Check verticals
		if(AIboard[0][i] == playerChar && AIboard[1][i] == playerChar && AIboard[2][i] == playerChar)
			return true;
	}

	// Check diagonals
	if (AIboard[0][0] == playerChar && AIboard[1][1] == playerChar && AIboard[2][2] == playerChar) {
		return true;
	} else if (AIboard[0][2] == playerChar && AIboard[1][1] == playerChar && AIboard[2][0] == playerChar) {
		return true;
	}

	return false;
}

int Game::score(char AIboard[3][3]) {
	if(checkWin(HUMAN, AIboard)) { return 10; }
	else if(checkWin(AI, AIboard)) { return -10; }
	return 0; // draw
}

Move Game::minimax(char AIboard[3][3]) { 
	int bestMoveScore = 100; // -100 is arbitrary
	Move bestMove;
	bestMove.x = -1; bestMove.y = -1;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMoveScore = maxSearch(AIboard);
				if(tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMove;
}

int Game::maxSearch(char AIboard[3][3]) {
	if(gameOver(AIboard)) return score(AIboard);
	Move bestMove;
	bestMove.x = -1; bestMove.y = -1;

	int bestMoveScore = -1000;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = human;
				int tempMoveScore = minSearch(AIboard);
				if(tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

int Game::minSearch(char AIboard[3][3]) {
	if(gameOver(AIboard)) return score(AIboard);
	Move bestMove;
	bestMove.x = -1; bestMove.y = -1;

	int bestMoveScore = 1000; 
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMove = maxSearch(AIboard);
				if(tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

void Game::getHumanMove() {
	int x, y = -1; // arbitrary assignment to init loop
	while(x < 0 || x > 2 || y < 0 || y > 2) {
		// Loop until a valid move is entered
		cout << "Enter your move in coordinate form, ex: (1,3)." << endl;
		cout << "Your Move: ";
		char c;
		string restofline;
		cin >> c >> c;
		x = c - '0' - 1;
		cin >> c >> c;
		y = c - '0' - 1;
		getline(cin, restofline); // get garbage chars after move
	}
	board[x][y] = human;
}

void Game::play() {
	int turn = 0;
	printBoard(board);
	while(!checkWin(HUMAN, board) && !checkWin(AI, board) && !gameOver(board)) {
		// for(int i=0; i<3; i++) for(int j=0; j<3; j++) cout << board[i][j]; cout << endl;
		// human move
		if(turn % 2 == 0) {
			getHumanMove();
			if(checkWin(HUMAN, board)) cout << "Human Player Wins" << endl;
			turn++;
			printBoard(board);
		} else {
			cout << endl << "Computer Player Move:" << endl;
			Move AImove = minimax(board);
			// cout << AImove.x << " " << AImove.y << endl;
			board[AImove.x][AImove.y] = ai;
			if(checkWin(AI, board)) cout << "Computer Player Wins" << endl;
			turn++;
			printBoard(board);
		}
	}
}