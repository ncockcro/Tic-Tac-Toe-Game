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

int main() {
	// Initial objects
	Board gameBoard = Board();
	Player p1 = Player();
	AI ai = AI();

	cout << "Welcome to tic tac toe!" << endl;
	gameBoard.PrintBoard();

	// Picking pieces for the game
	p1.PickPiece();
	ai.CreatePiece(p1);

	// While the player doesn't quit the game...
	while(p1.GetCurrentMove1() != -1) {

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




	system("pause");
	return 0;
}