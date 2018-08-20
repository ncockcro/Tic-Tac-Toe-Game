/*
Written by: Nicholas Cockcroft
Date: August 12, 2018

Description: The "Board" class is responsible for handleing the tic tac toe board, error checking user input with the board,
and anything else that involves with the manipulation of the board.

*/
#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <array>
#include "Player.h"

using namespace std;


class Board {

public:
	// Public functions
	Board();
	~Board();
	void PrintBoard();
	bool CheckMove(int move1, int move2, char piece);
	char GameWon(char playerPiece, char aiPiece);

	// Getters
	string GetBoard();

// Private variables
private:
	// Private variables
	char board[3][3];

	// Private functions
	void AddMove(int move1, int move2, char piece);
	char CheckHorizontal();
	char CheckVerticle();
	char CheckLeftDiagnol();
	char CheckRightDiagnol();
	bool CheckTie();
};

#endif