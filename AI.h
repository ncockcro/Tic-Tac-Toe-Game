/*

Written by: Nicholas Cockcroft
Date: August 12, 2018

Description: The "AI" class is responsible for the AI of the tic tac toe game. Everything needed for the AI to perform properly
will be stored in this class.

*/
#ifndef AI_H
#define AI_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class AI
{
public:
	// Pubic functions
	AI();
	void CreatePiece(char playerPiece);
	void MakeMove(string board);
	void MakeAIBoard(string board);

	// Getters
	char GetPiece();
	char GetCurrentMove1();
	char GetCurrentMove2();

private:
	// Private variables
	char AIPiece;
	char enemysPiece;
	char AIBoard[3][3];
	char currentMove1;
	char currentMove2;
	int lastEducatedMove;

	// Private functions
	bool CheckHorizontal();
	bool CheckVerticle();
	bool CheckLeftDiagnol();
	bool CheckRightDiagnol();
	bool MiddleSpot();
	int EducatedMove();

};

#endif