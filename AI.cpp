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



AI::AI()
{
}


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

// Returns the ai piece
char AI::GetPiece() {
	return AIPiece;
}

void AI::ReadBoard(char **arr) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr[i][j] << endl;
		}
	}
}

void AI::MakeMove(string board) {

	MakeAIBoard(board);

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

	}
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

char AI::GetCurrentMove1() {
	return currentMove1;
}

char AI::GetCurrentMove2() {
	return currentMove2;
}

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

bool AI::CheckRightDiagnol() {
	int enemyCount = 0;
	int iPosition;
	int jPosition;
	int secondI = 2;

	for (int i = 0; i < 3; i++) {
		if (AIBoard[i][secondI] == enemysPiece || AIBoard[i][secondI] == AIPiece) {
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
