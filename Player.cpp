/*

Written by: Nicholas Cockcroft
Date: August 12, 2018

*/
#include "Player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Default constructor
Player::Player() {
	currentMove1 = -2;
	currentMove2 = -2;
}

// Default destructor
Player::~Player() {

}

// Prompts the user to pick a piece at the start of the program, either "X" or "O" and will then assign
// the ai to use the opposite piece
void Player::PickPiece() {
	bool valid = false;

	// Error checking to make sure the user types in either a "X" or "O"
	while (valid != true) {
		cout << "Pick either \"X\" or \"O\" for your piece: ";
		cin >> userPiece;
		valid = CheckPiece(userPiece);
	}
}

// Function for taking in a character the user typed in and checking if it is either a "X" or "O". Otherwise it will
// output to the user that they typed incorrectly and prompt them again
bool Player::CheckPiece(char piece) {
	char capitalizedPiece = toupper(piece);

	if (capitalizedPiece == 'X' || capitalizedPiece == 'O') {
		return true;
	}
	else {
		cout << "Incorrect piece, enter either \"X\" or \"O\"." << endl;
		return false;
	}
}

// Returns the piece that user has
char Player::GetPiece() {
	return userPiece;
}

// Prompts the user to make a move and have them enter the coordinates of where they want there piece to be
bool Player::MakeMove() {
	string temp;

	cout << "Enter where you want to place " << userPiece << " in the form (#,#). Type 'q' to quit: ";
	cin >> temp;

	if (temp == "q") {
		cout << "The player quits." << endl;
		exit(1);
		currentMove1 = -1;
		return true;
	}

	// If the user types in a valid move, we will parse it as normal and store the coordinates
	if (CheckMove(temp)) {
		istringstream ss(temp);
		string token;
		int count = 0;

		while (getline(ss, token, ',')) {
			if (count == 0) {
			currentMove1 = stoi(token);
			count++;
		}

			if (count == 1) {
				currentMove2 = stoi(token);
			}
		}
		return true;
	}
	else {
		cout << "Error: Incorrect position. Pick a spot in the form (#,#)." << endl;
		return false;
	}
	
}

// Checks the most recent move the user typed in and checking to make sure they entered it in the correct format
// and entered numbers that are within the size of the board
bool Player::CheckMove(string temp) {
	istringstream ss(temp);
	string token;
	int count = 0;

	while (getline(ss, token, ',')) {
		if (IsDigits(token)) {
			if (stoi(token) > -1 && stoi(token) < 3) {
				count++;
			}
		}
	}
	if (count == 2) {
		return true;
	}
	else {
		return false;
	}
}

// Checks if a string that is passed into it is a number of not.
bool Player::IsDigits(string &num) {
	return all_of(num.begin(), num.end(), ::isdigit);
}

// Gets the i index of the 2d array
int Player::GetCurrentMove1() {
	return currentMove1;
}

// Gets the j index of the 2d array
int Player::GetCurrentMove2() {
	return currentMove2;
}