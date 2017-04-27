/***************************************************************************************/
/*  YOU ARE NOT ALLOWED TO CHANGE THIS FILE EXCEPT TWO INCLUDE LINES MENTIONED BELOW.  */
/*  HOWEVER YOU HAVE TO SUBMIT THIS FILE TOGETHER WITH THE CLASS HEADER AND            */
/*  IMPLEMENTATION FILES FOR BOARD AND PLAYER CLASSES.                                 */
/***************************************************************************************/

#include <iostream>
#include "Board.h"  //edit this line to include your header file
#include "Player.h" //edit this line to include your header file
#include <string>
#include "strutils.h"

using namespace std;

//tries to read a non-negative integer until it is entered. The entire line must contain such an integer.
//returns read valid integer
int readInt()
{
	string input;
	bool done = false;

	while (done == false)  //continue until a non-negative integer is entered
	{ 
		getline(cin, input);  //read entire line
		if (input.length() > 0)  //if there is data on the line
		{
			done = true;
			for (unsigned int i = 0; i < input.length(); i++)
				if (input[i] < '0' || input[i] > '9') //if something other than a digit is seen
					done = false; //do not accept
		}

		if (done == false)  //if the entered data is not a non-negative integer
			cout << "Please enter a non-negative integer: ";
	}

	return atoi(input);  //return the integer
}

int main()
{
	//create a board with all cells initialized to dash character '-'
	Board gameBoard = Board();

	char piece1, piece2; //pieces of players
	string input;
	
	//Reading the piece character of player 1 and checking the rules
	cout << "Please enter a character for the first player's piece: ";
	getline(cin, input);
	if (input.length() != 1) //input should be one character. If the input is more than one character
	{
		cout << "You have to enter one character. Exiting program.." << endl;
		system("pause");
		return 0; //terminate
	}
	else if ( input[0] < 33 || input[0] > 126 || input.at(0) == '-') //check if valid character
	{
		cout << "You entered an invalid character. Exiting program.." << endl;
		system("pause");
		return 0; //terminate
	}
	else
		piece1 = input[0]; //first piece is successfully read


	//Reading the piece character of player 2 and checking the rules
	cout << "Please enter a character for the second player's piece: ";
	getline(cin, input);
	if (input.length() != 1) //input should be one character. If the input is more than one character
	{
		cout << "You have to enter one character. Exiting program.." << endl;
		system("pause");
		return 0; //terminate
	}
	else if ( input[0] < 33 || input[0] > 126 || input.at(0) == '-') //check if valid character
	{
		cout << "You entered an invalid character. Exiting program.." << endl;
		system("pause");
		return 0; //terminate
	}
	else
		piece2 = input[0]; //second piece is successfully read


	if (piece1 == piece2) //The pieces must be different. If they are same
	{
		cout << "The pieces of players must be different. Exiting program.." << endl;
		system("pause");
		return 0; //terminate
	}

	//create 2 player objects
	//they share the same game board
	Player p1 = Player(gameBoard, piece1); 
	Player p2 = Player(gameBoard, piece2); 

	cout << endl << "Game has started.." << endl;
	cout << "The board is initially " << endl << endl;
	gameBoard.DisplayBoard();  //Display the empty board

	bool gameOver = false; //Boolean variable to check if game is finished
	int column; //variable to read column input
	 
	//game begins
	while (gameOver == false)  //while the game is not finished
	{
		cout << endl << "p1's turn. To play, please enter a column number in range [0, 3]: ";
		column = readInt(); //read a valid non-negative integer using previously defined function readInt
		
		while (p1.play(column) == false) //try until successful move
		{
			cout << "Invalid move. " << endl
				 << "Please enter a column number in range [0, 3]: ";
			column = readInt(); //column input again
		}

		cout << endl << "After p1's move, the board: " << endl << endl;
		gameBoard.DisplayBoard(); 
		
		if (p1.isWinner() == true) //p1 may win after her move, check it!
			gameOver = true;

		if (gameOver == false) //if game is not over, it is p2's turn
		{
			cout << endl << "p2's turn. To play, please enter a column number in range [0, 3]: ";
			column = readInt(); //p2's move is read
		
			while (p2.play(column) == false) //try until successful move
			{
				cout << "Invalid move. " << endl
				 << "Please enter a column number in range [0, 3]: ";
				column = readInt(); //column input again
			}

			cout << endl << "After p2's move, the board: " << endl << endl;
			gameBoard.DisplayBoard();

			if (p2.isWinner() == true) //p2 may win after her move, check it!
				gameOver = true;
		}

		if (gameBoard.isFull() == true) //board full -> draw -> game ends
			gameOver = true;
	}
	
	//game ended, check the result
	cout << endl << "Game is over.." << endl;
	if (p1.isWinner() == true)
		cout << "p1 is the winner." << endl;
	else if (p2.isWinner() == true)
		cout << "p2 is the winner." << endl;
	else
		cout << "Draw. There is no winner..." << endl;

	system("pause");
	return 0;
}