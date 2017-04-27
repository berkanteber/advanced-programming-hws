#include <iostream>
#include "berkanteber_Teber_Berkan_HW6_board.h"

using namespace std;


Board::Board ()										// constructor
{
	// fills the board with dashes
	for (int i = 0; i < 5; i++)		
		for (int j = 0; j < 4; j++)
			myBoard[i][j] = '-';
}

void Board::DisplayBoard () const					// displays the board
{
	for (int i = 0; i < 5; i++, cout << endl)
		for (int j = 0; j < 4; j++)
			cout << myBoard[i][j] << " ";	
	cout << endl;
}

bool Board::dropPieceOn (int column, char piece)	// drops given piece to given column
{
	if (column < 0 || column > 3)	// checks the column is valid
		return false;
	if (myBoard[0][column] != '-')	// checks if the column is full
		return false;
	
	// finds the first empty row from bottom to top
	int emptyRow = 4;
	while (emptyRow >= 0 && myBoard[emptyRow][column] != '-')
		emptyRow --;
	
	myBoard[emptyRow][column] = piece;
	return true;
}

bool Board::isFull () const							// checks if the board is full
{
	bool full = true;

	for (int column = 0; full && column <= 3; column++)	// 1 dash is enough to say "not full"
		if (myBoard[0][column] == '-')
			full = false;

	return full;
}	

bool Board::isConnect3 (char piece) const			// checks if there is 3 connected pieces of given kind
{
	bool connected = false;

	// check horizontal
	for (int row = 0; !connected && row <= 4; row++)
	{
		if (!connected && myBoard[row][0] == piece && myBoard[row][1] == piece && myBoard[row][2] == piece)
			connected = true;

		if (!connected && myBoard[row][1] == piece && myBoard[row][2] == piece && myBoard[row][3] == piece)
			connected = true;
	}

	// check vertical
	for (int col = 0; !connected && col <= 3; col++)
	{
		if (!connected && myBoard[0][col] == piece && myBoard[1][col] == piece && myBoard[2][col] == piece)
			connected = true;

		if (!connected && myBoard[1][col] == piece && myBoard[2][col] == piece && myBoard[3][col] == piece)
			connected = true;
		
		if (!connected && myBoard[2][col] == piece && myBoard[3][col] == piece && myBoard[4][col] == piece)
			connected = true;
	}

	// check diagonal (top-left to bottom-right)
	for (int row = 0; !connected && row <= 2; row ++)
	{
		if (!connected && myBoard[row][0] == piece && myBoard[row + 1][1] == piece && myBoard[row + 2][2] == piece)
			connected = true;

		if (!connected && myBoard[row][1] == piece && myBoard[row + 1][2] == piece && myBoard[row + 2][3] == piece)
			connected = true;	
	}

	// check antidiagonal	(bottom-left to top-right)
	for (int row = 0; !connected && row <= 2; row ++)
	{
		if (!connected && myBoard[row][2] == piece && myBoard[row + 1][1] == piece && myBoard[row + 2][0] == piece)
			connected = true;

		if (!connected && myBoard[row][3] == piece && myBoard[row + 1][2] == piece && myBoard[row + 2][1] == piece)
			connected = true;	
	}

	return connected;
}