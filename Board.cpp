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

	// If the player hasn't made a move yet, just return false
	if (move1 == -2 && move2 == -2) {
		return false;
	}
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

// Checks to see if either the player or the ai won the game. Checks horizontally for wins, checks vertically
char Board::GameWon(char playerPiece, char aiPiece) {

	if (CheckHorizontal() == playerPiece || CheckVerticle() == playerPiece || CheckLeftDiagnol() == playerPiece || CheckRightDiagnol() == playerPiece) {
		cout << "You won! I should have made the AI harder." << endl;
		return true;
	}
	else if (CheckHorizontal() == aiPiece || CheckVerticle() == aiPiece || CheckLeftDiagnol() == aiPiece || CheckRightDiagnol() == aiPiece) {
		cout << "The ai won. Try harder next time." << endl;
		return true;
	}
	else if (CheckTie()) {
		cout << "The game is a tie! You both are too good." << endl;
		return true;
	}
	else {
		return false;
	}

}

// Returns the entire board in the form of a string seperated by commas to be parsed by another function in another class
// That way another class can't modify the original board
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

// After validating that a move is correct, this function adds it to the board
void Board::AddMove(int move1, int move2, char piece) {
	board[move1][move2] = tolower(piece);
	PrintBoard();
}

char Board::CheckHorizontal() {
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
	return 'a';
}
char Board::CheckVerticle() {
	int xCount = 0;
	int oCount = 0;

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
	return 'a';
}
char Board::CheckLeftDiagnol() {
	int secondI = 0;
	int xCount = 0;
	int oCount = 0;

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
	return 'a';
}
char Board::CheckRightDiagnol() {
	// Checking for diagnol wins going from top right to bottom left
	int secondI = 2;
	int xCount = 0;
	int oCount = 0;

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
	return 'a';
}

bool Board::CheckTie() {

	int occupied = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 'x' || board[i][j] == 'o') {
				occupied++;
			}
		}
	}

	if (occupied == 9) {
		return true;
	}
	else {
		return false;
	}
}