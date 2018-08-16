/*

Written by: Nicholas Cockcroft
Date: August 8, 2018

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

		// Have the player make a move
		p1.MakeMove();

		// Validate that move and print the board to show
		if (p1.GetCurrentMove1() != -1) {
			while (!gameBoard.CheckMove(p1.GetCurrentMove1(), p1.GetCurrentMove2(), p1.GetPiece())) {
				p1.MakeMove();
			}
			gameBoard.PrintBoard();


			if (gameBoard.GameWon() == p1.GetPiece()) {
				cout << "Congratualtions! You won!" << endl;
				break;
			}
			if (gameBoard.GameWon() == ai.GetPiece()) {
				cout << "The AI won." << endl;
				break;
			}

			// Sleep for 1 second
			this_thread::sleep_for(chrono::milliseconds(1000));

			// Have the ai make a move
			ai.MakeMove(gameBoard.GetBoard());

			gameBoard.CheckMove(ai.GetCurrentMove1(), ai.GetCurrentMove2(), ai.GetPiece());
			gameBoard.PrintBoard();
		}
	}




	system("pause");
	return 0;
}