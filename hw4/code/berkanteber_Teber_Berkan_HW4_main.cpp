/************************************************************

Berkan Teber berkanteber 19080

*************************************************************

This program searches a pattern in a given matrix.

************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "berkanteber_Teber_Berkan_HW4_stack.h"

using namespace std;

// cell struct for matrix
struct cell
{
	char character;
	bool flag;
};


// fills the matrix with the values taken from the input
void fillMatrix (cell** &, int, int);

// searches for the pattern in the matrix
void search (const string &, int, cell**, int, int, const int &, const int &, Stack &, bool &);

// prints the stack (returns false for an empty stack)
bool printStack(Stack);

// makes all flags false
void fixFlags(cell** &, const int, const int);

// deletes the matrix
void deleteMatrix (cell** &, int);

// deletes the stack
void deleteStack (Stack &);


int main()
{
	int rows, cols;
	
	cout	<< "Please enter the number of rows: ";
	cin		>> rows;
	cout	<< "Please enter the number of columns: ";
	cin		>> cols;
	

	// create a dynamic matrix
	cell** matrix = new cell* [rows];
	for (int i = 0; i < rows; i++)
		matrix[i] = new cell[cols];

	// fill the matrix with the values taken from the input
	fillMatrix(matrix, rows, cols);

	string searchPattern;
	cout	<< "--------------------------------------------------------------" << endl
			<< "Please enter a string of bits to search (CTRL+Z to quit): ";
	while (cin >> searchPattern)	// until ^Z is taken as input
	{
		Stack stack;		// to keep track
		bool found = false;	// to check if there is any path found

		// search for searchPattern starting with index = 0 in matrix from (0, 0)
		search (searchPattern, 0, matrix, 0, 0, rows, cols, stack, found);
		
		// make all the flags false
		fixFlags(matrix, rows, cols);

		if (found == true) // there is a path
		{			
			cout << "The bit string " << searchPattern << " is found following these coordinates: " << endl;
			printStack (stack);	// print the stack
			cout << endl;
		}

		else
		{
			cout << "The bit string " << searchPattern << " could not be found. " << endl;	
			deleteStack (stack);	// delete the stack
		}

		cout	<< "--------------------------------------------------------------" << endl
				<< "Please enter a string of bits to search (CTRL+Z to quit): ";
	


	}

	deleteMatrix (matrix, rows);	// delete the matrix

	return 0;
}

// fills the matrix with the values taken from the input
void fillMatrix (cell** &matrix, int rows, int cols)
{
	ifstream inputFile;
	string fileName;

	cout	<< "Please enter the name of the input file: ";
	cin		>> fileName;

	// open input file
	inputFile.open (fileName.c_str());
	while (inputFile.fail())			// retake the file name until there is no problem
	{
		cout	<< "File cannot be opened." << endl
				<< "Please enter the name of the input file again: " ;
		cin		>> fileName;

		inputFile.clear();
		inputFile.open(fileName.c_str());
	}

	char ch;

	// fill the matrix
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			inputFile >> ch;
			matrix[i][j].character = ch;
			matrix[i][j].flag = false;
		}

	inputFile.close();

	return;
}

// searches for the pattern in the matrix
void search (const string &pattern, int index, cell** matrix, int x, int y, const int &rows, const int &cols, Stack &stack, bool &found)
{
	// limit the index, and the coordinates
	if (index >= pattern.length() || x >= rows || y >= cols)
		return;

	// return if there is a match already or the coordinates which are dead-end
	if (found == true || matrix[x][y].flag == true)
		return;
	
	// mark the cell as true since it doesn't match with the charcter
	if (matrix[x][y].character != pattern[index])
		matrix[x][y].flag = true;

	if (matrix[x][y].flag == false)
	{	
		stack.push (x, y);	

		if (index == pattern.length() - 1) // it is the last character
			found = true;
			
		else
		{
			search (pattern, index + 1, matrix, x, y + 1, rows, cols, stack, found);	// continue to path from right		
			search (pattern, index + 1, matrix, x + 1, y, rows, cols, stack, found);	// continue to path from down

			if (found == false)	// this point is also dead-end
			{
				matrix[x][y].flag = true;			
				stack.pop(x, y);
			}
		}
	}	

	return;
}

// prints the stack (returns false for an empty stack)
bool printStack (Stack stack)
{
	if (stack.isEmpty())
		return false;

	else
	{
		int x, y;
		stack.pop (x, y);
		if(printStack(stack)) // to prevent 1 extra '-'
			cout << " - ";
		cout << "(" << x << ", " << y << ")";
		return true;
	}
}

// makes all flags false
void fixFlags (cell** &matrix, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j].flag = false;

	return;
}

// deletes the matrix
void deleteMatrix (cell** &matrix, int rows)
{
	for (int i = 0; i < rows; i++)
		delete [] matrix[i];

	delete [] matrix; 
	
	return;
}

// deletes the stack
void deleteStack(Stack &stack)
{
	int x, y;

	while (!stack.isEmpty())
		stack.pop(x, y);
		
	return;
}