/*

Written by: Nicholas Cockcroft
Date: August 12, 2018

Description: The "Player" class is responsible for taking user input, ensuring it is valid, and anything pertaining to
the player.

*/
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Player
{
public:
	// Public functions
	Player();
	void PickPiece();
	bool CheckPiece(char piece);
	bool MakeMove();
	bool CheckMove(string temp);
	bool IsDigits(string &num);

	// Getters
	char GetPiece();
	int GetCurrentMove1();
	int GetCurrentMove2();

private:
	// Private variables
	char userPiece;
	int currentMove1;
	int currentMove2;
};

#endif