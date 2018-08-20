/*

Written by: Nicholas Cockcroft
Date: August 12, 2018

*/
#include "AI.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


// Default constructor
AI::AI()
{
}

// Default destructor
AI::~AI()
{
}

// Creates a piece for the ai to use. Is dependent upon which piece the user picked
void AI::CreatePiece(Player &p) {
	if (p.GetPiece() == 'x') {
		AIPiece = 'o';
		enemysPiece = 'x';
	}
	else {
		AIPiece = 'x';
		enemysPiece = 'o';
	}
}

void AI::ReadBoard(char **arr) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr[i][j] << endl;
		}
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

	// If the player isn't about to win, the ai will try to get three in a row
	EducatedMove();
}

// Function for taking the string format of the board that the board class sent and deconstructs it back into a 2d array to be used for the 
// ai to make its moves
void AI::MakeAIBoard(string board) {
	
	istringstream ss(board);
	string token;

	int iCount = 0;
	int jCount = 0;
	int count = 0;

	// Spitting on commas and every character in there is an element of the board 2d array
	while (getline(ss, token, ',')) {
		AIBoard[iCount][jCount] = token[0];
		count++;
		jCount++;

		if (count == 3) {
			iCount++;
			jCount = 0;
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

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (AIBoard[i][j] == enemysPiece || AIBoard[i][j] == AIPiece) {
				enemyCount++;
			}
			if (AIBoard[i][j] == '*') {
				iPosition = i;
				jPosition = j;
			}
		}

		if (enemyCount == 2) {
			currentMove1 = iPosition;
			currentMove2 = jPosition;
			return true;
		}
		enemyCount = 0;
	}

	return false;
}

// Checks if the player is about to have a verticle win and will counter act by placing a piece to block them
bool AI::CheckVerticle() {
	int enemyCount = 0;
	int iPosition;
	int jPosition;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (AIBoard[j][i] == enemysPiece || AIBoard[i][j] == AIPiece) {
				enemyCount++;
			}
			if (AIBoard[j][i] == '*') {
				iPosition = i;
				jPosition = j;
			}
		}

		if (enemyCount == 2) {
			currentMove1 = jPosition;
			currentMove2 = iPosition;
			return true;
		}
		enemyCount = 0;
	}

	return false;
}

// Checks if the player is about to have a left diagnol win and will counter act by placing a piece to block them
bool AI::CheckLeftDiagnol() {
	int enemyCount = 0;
	int iPosition;
	int jPosition;
	int secondI = 0;

	for (int i = 0; i < 3; i++) {
		if (AIBoard[i][secondI] == enemysPiece || AIBoard[i][secondI] == AIPiece) {
			enemyCount++;
		}
		if (AIBoard[i][secondI] == '*') {
			iPosition = i;
			jPosition = secondI;
		}
		secondI++;
	}

	if (enemyCount == 2) {
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

	for (int i = 0; i < 3; i++) {
		if (AIBoard[i][secondI] == enemysPiece) {
			enemyCount++;
		}
		if (AIBoard[i][secondI] == '*') {
			iPosition = i;
			jPosition = secondI;
		}
		if (enemyCount == 2) {
			currentMove1 = iPosition;
			currentMove2 = jPosition;
			return true;
		}
		secondI--;
	}

	return false;
}

void AI::EducatedMove() {
	int emptyCount = 0;

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
			return;
		}
		emptyCount = 0;
	}

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
			return;
		}
		emptyCount = 0;
	}

	// Making a left diagnol move
	int secondI = 2;
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
}