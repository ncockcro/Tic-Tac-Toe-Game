/*

Written by: Nicholas Cockcroft
Date: August 13, 2018

*/
#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


// default constructor for the board class
Board::Board()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '*';
		}
	}
}

// Default destructor for the board class
Board::~Board()
{
}

void Board::CreateBoard() {

}

// Prints the current board
void Board::PrintBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "|" << board[i][j];
		}
		cout << "|" << endl;
		cout << "-------" << endl;
	}
}

// Function for checking if a move the player entered is being placed on an empty spot on the board or not
bool Board::CheckMove(int move1, int move2, char piece) {
	// If it is a blank spot, put the piece there
	if (board[move1][move2] == '*') {
		AddMove(move1, move2, piece);
		return true;
	}
	// Otherwise, return false and prompt the user again for a new position
	else {
		cout << "There is already a piece there! Pick a different spot." << endl;
		return false;
	}
}

// After validating that a move is correct, this function adds it to the board
void Board::AddMove(int move1, int move2, char piece) {
	board[move1][move2] = tolower(piece);
}

// Checks to see if either the player or the ai won the game. Checks horizontally for wins, checks vertically
char Board::GameWon() {
	int xCount = 0;
	int oCount = 0;

	// Checks for any wins horizontally
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 'x') {
				xCount++;
			}
			if (board[i][j] == 'o') {
				oCount++;
			}

			if (xCount == 3) {
				return 'x';
			}

			if (oCount == 3) {
				return 'o';
			}
		}
		xCount = 0;
		oCount = 0;
	}

	// Checks for any vertical wins
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[j][i] == 'x') {
				xCount++;
			}
			if (board[j][i] == 'o') {
				oCount++;
			}

			if (xCount == 3) {
				return 'x';
			}

			if (oCount == 3) {
				return 'o';
			}
		}
		xCount = 0;
		oCount = 0;
	}

	int secondI = 0;
	// Checking for diagnol wins going from top left to bottom right
	for (int i = 0; i < 3; i++) {
		if (board[i][secondI] == 'x') {
			xCount++;
		}
		if (board[i][secondI] == 'o') {
			oCount++;
		}
		secondI++;
	}

	if (xCount == 3) {
		return 'x';
	}

	if (oCount == 3) {
		return 'o';
	}

	// Checking for diagnol wins going from top right to bottom left
	secondI = 2;
	xCount = 0;
	oCount = 0;
	for (int i = 0; i < 3; i++) {
		if (board[i][secondI] == 'x') {
			xCount++;
		}
		if (board[i][secondI] == 'o') {
			oCount++;
		}
		secondI--;
	}

	if (xCount == 3) {
		return 'x';
	}

	if (oCount == 3) {
		return 'o';
	}

}

string Board::GetBoard() {
	string fullBoard;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			fullBoard += board[i][j];
			fullBoard += ',';
		}
	}

	return fullBoard;
}