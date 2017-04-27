#include "berkanteber_Teber_Berkan_HW6_board.h"
#include "berkanteber_Teber_Berkan_Hw6_player.h"

using namespace std;


bool Player::play (int column)	// plays given column
{
	return board.dropPieceOn (column, piece);	// uses board object's member function to play
}

bool Player::isWinner ()		// checks if the player is given
{
	return board.isConnect3 (piece);			// uses board object's member function to check if there is 3 connected pieces of given kþnd
}