#ifndef _BERKANTEBER_TEBER_BERKAN_HW6_BOARD_H
#define _BERKANTEBER_TEBER_BERKAN_HW6_BOARD_H

using namespace std;


class Board
{
private:
		char myBoard [5][4];						// board
public:	
		Board ();									// constructor							
		void DisplayBoard () const;					// displays the board
		bool dropPieceOn (int column, char piece);	// drops given piece to given column
		bool isFull () const;						// checks if the board is full
		bool isConnect3 (char piece) const;			// checks if there is 3 connected pieces of given kind
};

#endif