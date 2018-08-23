/*

Written by: Nicholas Cockcroft
Date: August 12, 2018

*/
#include "AI.h"

AI::AI() {
	lastEducatedMove = 0;
}

// Creates a piece for the ai to use. Is dependent upon which piece the user picked
void AI::CreatePiece(char playerPiece) {
	if (playerPiece == 'x') {
		AIPiece = 'o';
		enemysPiece = 'x';
	}
	else {
		AIPiece = 'x';
		enemysPiece = 'o';
	}
}

// This function is called in main and acceptes the string of what the board is at a current time. A function will be called
// which converts the string of the board into a 2d array for which the ai class can store and have access to without having
// any access to the actual game board. From there, there are a series of other functions to be called which will check if the player is about
// to win in a number of scenaries and will then block the player. If the player isn't about to win, then the ai will make its own move to try 
// and win.
void AI::MakeMove(string board) {

	cout << "------------- AI's move -------------" << endl;

	MakeAIBoard(board);

	// Checks if the player is going to win with a horizontal, verticle, or diagnol win
	if (CheckHorizontal()) {
		return;
	}
	if (CheckVerticle()) {
		return;
	}
	if (CheckLeftDiagnol()) {
		return;
	}
	if (CheckRightDiagnol()) {
		return;
	}
	if (MiddleSpot()) {
		return;
	}

	// If the player isn't about to win, the ai will try to get three in a row
	lastEducatedMove = EducatedMove();
}

// Function for taking the string format of the board that the board class sent and deconstructs it back into a 2d array to be used for the 
// ai to make its moves
void AI::MakeAIBoard(string board) {

	int letterCount = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			AIBoard[i][j] = board[letterCount];
			letterCount++;
		}
	}
	
}

// Returns the ai piece
char AI::GetPiece() {
	return AIPiece;
}

// Returns the ai's move for the first column in a 2d array
char AI::GetCurrentMove1() {
	return currentMove1;
}

// Returns the ai's move for the second column in a 2d array
char AI::GetCurrentMove2() {
	return currentMove2;
}

// Checks if the player is about to have a horizontal win and will counter act by placing a piece to block them
bool AI::CheckHorizontal() {
	int enemyCount = 0;
	int iPosition;
	int jPosition;
	bool computerPiece = false;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (AIBoard[i][j] == enemysPiece) {
				enemyCount++;
			}
			if (AIBoard[i][j] == '*') {
				iPosition = i;
				jPosition = j;
			}
			if (AIBoard[i][j] == AIPiece) {
				computerPiece = true;
			}
		}

		if (enemyCount == 2 && computerPiece != true) {
			currentMove1 = iPosition;
			currentMove2 = jPosition;
			return true;
		}
		enemyCount = 0;
		computerPiece = false;
	}

	return false;
}

// Checks if the player is about to have a verticle win and will counter act by placing a piece to block them
bool AI::CheckVerticle() {
	int enemyCount = 0;
	int iPosition;
	int jPosition;
	bool computerPiece = false;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (AIBoard[j][i] == enemysPiece) {
				enemyCount++;
			}
			if (AIBoard[j][i] == '*') {
				iPosition = i;
				jPosition = j;
			}
			if (AIBoard[j][i] == AIPiece) {
				computerPiece = true;
			}
		}

		if (enemyCount == 2 && computerPiece != true) {
			currentMove1 = jPosition;
			currentMove2 = iPosition;
			return true;
		}
		enemyCount = 0;
		computerPiece = false;
	}

	return false;
}

// Checks if the player is about to have a left diagnol win and will counter act by placing a piece to block them
bool AI::CheckLeftDiagnol() {
	int enemyCount = 0;
	int iPosition;
	int jPosition;
	int secondI = 0;
	bool computerPiece = false;

	for (int i = 0; i < 3; i++) {
		if (AIBoard[i][secondI] == enemysPiece) {
			enemyCount++;
		}
		if (AIBoard[i][secondI] == '*') {
			iPosition = i;
			jPosition = secondI;
		}
		if (AIBoard[i][secondI] == AIPiece) {
			computerPiece = true;
		}
		secondI++;
	}

	if (enemyCount == 2 && computerPiece != true) {
		currentMove1 = jPosition;
		currentMove2 = iPosition;
		return true;
	}

	return false;
}

// Checks if the player is about to have a right diagnol win and will counter act by placing a piece to block them
bool AI::CheckRightDiagnol() {
	int enemyCount = 0;
	int iPosition;
	int jPosition;
	int secondI = 2;
	bool computerPiece = false;

	for (int i = 0; i < 3; i++) {
		if (AIBoard[i][secondI] == enemysPiece) {
			enemyCount++;
		}
		if (AIBoard[i][secondI] == '*') {
			iPosition = i;
			jPosition = secondI;
		}
		if (AIBoard[i][secondI] == AIPiece) {
			computerPiece = true;
		}
		secondI--;
	}

	if (enemyCount == 2 && computerPiece != true) {
		currentMove1 = iPosition;
		currentMove2 = jPosition;
		return true;
	}
	return false;
}

bool AI::MiddleSpot() {
	if (AIBoard[1][1] == '*') {
		currentMove1 = 1;
		currentMove2 = 1;
		return true;
	}
	return false;
}

// If the ai checks and the player isn't about to win any of its moves, then the ai will try and get 3 in a row
int AI::EducatedMove() {
	int emptyCount = 0;
	int secondI = 0;
	srand(time(NULL));

	if (lastEducatedMove == 0) {
		lastEducatedMove = rand() % 4 + 1;
	}

	if (lastEducatedMove == 1) {
		// Making a horizontal move
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (AIBoard[i][j] == '*') {
					emptyCount++;
					currentMove1 = i;
					currentMove2 = j;
				}
				if (AIBoard[i][j] == AIPiece) {
					emptyCount++;
				}
			}

			if (emptyCount == 3) {
				return 1;
			}
			emptyCount = 0;
		}
		return 0;
	}

	if (lastEducatedMove == 2) {
		// Making a verticle move
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (AIBoard[j][i] == '*') {
					emptyCount++;
					currentMove1 = j;
					currentMove2 = i;
				}
				if (AIBoard[j][i] == AIPiece) {
					emptyCount++;
				}
			}

			if (emptyCount == 3) {
				return 2;
			}
			emptyCount = 0;
		}
		return 0;
	}

	if (lastEducatedMove == 3) {
		// Making a left diagnol move
		secondI = 0;
		emptyCount = 0;
		for (int i = 0; i < 3; i++) {
			if (AIBoard[i][secondI] == '*') {
				emptyCount++;
				currentMove1 = i;
				currentMove2 = secondI;
			}
			if (AIBoard[i][secondI] == AIPiece) {
				emptyCount++;
			}
			secondI++;
		}
		if (emptyCount == 3) {
			return 3;
		}
		return 0;
	}

	if (lastEducatedMove == 4) {
		secondI = 2;
		emptyCount = 0;
		for (int i = 0; i < 3; i++) {
			if (AIBoard[i][secondI] == '*') {
				emptyCount++;
				currentMove1 = i;
				currentMove2 = secondI;
			}
			if (AIBoard[i][secondI] == AIPiece) {
				emptyCount++;
			}
			secondI--;
		}
		if (emptyCount == 3) {
			return 4;
		}
		return 0;
	}
}