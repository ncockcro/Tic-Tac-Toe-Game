/*

Written by: Nicholas Cockcroft
Date: August 12, 2018

*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Board.h"
#include "Player.h"
#include "AI.h"

using namespace std;

bool PlayAgain();

int main() {
	
	// This boolean and function will have the game keep playing until the user is ready to stop
	bool willPlay = true;

	while(willPlay) {
		willPlay = PlayAgain();
	}

	return 0;
}

bool PlayAgain() {
	// Initial objects
	Board gameBoard = Board();
	Player p1 = Player();
	AI ai = AI();

	char willPlay;

	cout << "Welcome to tic tac toe!" << endl;
	gameBoard.PrintBoard();

	// Picking pieces for the game
	p1.PickPiece();
	ai.CreatePiece(p1.GetPiece());

	// While the player doesn't quit the game...
	while (p1.GetCurrentMove1() != -1) {

		p1.MakeMove();

		// Validate that move and print the board to show
		while (!gameBoard.CheckMove(p1.GetCurrentMove1(), p1.GetCurrentMove2(), p1.GetPiece())) {
			while (!p1.MakeMove()) {

			}
		}

		// Check to see if the player one after making their most recent move
		if (gameBoard.GameWon(p1.GetPiece(), ai.GetPiece())) {
			break;
		}

		this_thread::sleep_for(chrono::milliseconds(1000));

		// Have the ai make a move
		ai.MakeMove(gameBoard.GetBoard());
		gameBoard.CheckMove(ai.GetCurrentMove1(), ai.GetCurrentMove2(), ai.GetPiece());

		// Check to see if the ai won after making their most recent move
		if (gameBoard.GameWon(p1.GetPiece(), ai.GetPiece())) {
			break;
		}

	}

	// After the loop has completed, this will prompt the user if they want to play again or not
	do {
		cout << "Do you want to play again? ";
		cin >> willPlay;
	} while (toupper(willPlay) != 'Y' && toupper(willPlay) != 'N');

	if (toupper(willPlay) == 'Y') {
		return true;
	}
	else {
		return false;
	}
}