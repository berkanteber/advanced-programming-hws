/**************************************************

Berkan Teber 19080 berkanteber

***************************************************

HW1 -- The program takes a matrix from a file,
	-- and find series in the matric that sum up to
	-- given integer.

	-- I used the last lab exercise from first week, 
	-- and developed it for the homework.

**************************************************/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// sums the subvector horizontally in given range
int horizontalSumSubvector(const vector<vector<int>> & mat, int rowIndex, int startColIndex, int subvectorLength)
{
	int sum = 0;

	int endColIndex = startColIndex + subvectorLength - 1;	// the last column index of the subvector

	for(int i = startColIndex ; i <= endColIndex ; i++)
		sum += mat[rowIndex][i];

	return sum;
}

// sums the subvector vertically in given range
int verticalSumSubvector(const vector<vector<int>> & mat, int colIndex, int startRowIndex, int subvectorLength)
{
	int sum = 0;

	int endRowIndex = startRowIndex + subvectorLength - 1;	// the last row index of the subvector

	for(int i = startRowIndex ; i <= endRowIndex ; i++)
		sum += mat[i][colIndex];

	return sum;
}

// searchs for the sum in all horizontal subvectors	// returns total matches
int searchHorizontally (const vector<vector<int>> & mat, int sum, int rows, int cols)
{
	int totalOccurance = 0;

	for (int subvectorLength = 1; subvectorLength <= cols ; subvectorLength++)					// for all subvector sizes
		for (int rowIndex = 0; rowIndex < rows ; rowIndex++)									// for each row
			for(int subStarts = 0 ; subStarts < cols - subvectorLength + 1 ; subStarts++)		// subvector starts at each column index
				if (sum == horizontalSumSubvector(mat, rowIndex, subStarts, subvectorLength))	// checks if sum equals the sum of subvector -- verticalSumSubvector calculates the sum of subvector
				{
					cout	<< "Found one horizontally "
							<< "from (" << rowIndex << ", " << subStarts << ") "
							<< "to (" << rowIndex << ", " << subStarts + subvectorLength - 1 << ") ."
							<< endl;

					totalOccurance++;
				}

	return totalOccurance;
}

// searchs for the sum in all vertical subvectors	//  returns total matches
int searchVertically (const vector<vector<int>> & mat, int sum, int rows, int cols)
{
	int totalOccurance = 0;

	for (int subvectorLength = 1; subvectorLength <= rows ; subvectorLength++)					// for all subvector sizes
		for (int colIndex = 0; colIndex < cols ; colIndex++)									// for each column
			for(int subStarts = 0 ; subStarts < rows - subvectorLength + 1 ; subStarts++)		// subvector starts at each row index
				if (sum == verticalSumSubvector(mat, colIndex, subStarts, subvectorLength))	// checks if sum equals the sum of subvector -- verticalSumSubvector calculates the sum of subvector
				{
					cout	<< "Found one vertically "
							<< "from (" << subStarts << ", " << colIndex << ") "
							<< "to (" << subStarts + subvectorLength - 1 << ", " << colIndex << ") ."
							<< endl;

					totalOccurance++;
				}

	return totalOccurance;
}

// searchs for the sum in all horizontal and vertical subvectors	// returns total matches
int search (const vector<vector<int>> & mat, int sum, int rows, int cols)
{
	return searchHorizontally(mat, sum, rows, cols) + searchVertically(mat, sum, rows, cols);
}

int main()
{
	ifstream inputFile;
	string fileName;

	cout	<< "Please enter the name of the input file: ";
	cin		>> fileName;

	inputFile.open(fileName.c_str());
	while (inputFile.fail())			// retake the file name until there is no problem
	{
		cout	<< "File cannot be opened." << endl
				<< "Please enter the name of the input file again: " ;
		cin		>> fileName;

		inputFile.clear();
		inputFile.open(fileName.c_str());
	}

	vector<vector<int>> matrix;

	bool matrix_check = true;	// checks if the matrix is in correct form and if all the integers are positive
								// i didn't use "break" to exit the loop, but i checked the matrix_check for every loop instead

	int column = -1;				// i initialized column as -1, because	(i)		in first loop it doesn't check if temp.size() == column
								//										(ii)	there is no chance that size of a matrix is negative
	
	string line;
	while(!inputFile.eof() && matrix_check)	// continues unless the file ends or there is a problem
	{
		getline(inputFile, line);
		stringstream ssByChar(line);	// used to avoid forbidden characters
		stringstream ssByNum(line);		// used to get the numbers and form matrix
		
		char ch;
		while(matrix_check && ssByChar >> ch)			// checks if there are any characters other than a digit
			if(((ch >= '0') && (ch <= '9')) == false)
				matrix_check = false;
				
		int num;
		vector<int> temp;
		while(matrix_check && ssByNum >> num && num)			// (... && num) to avoid 0 as an integer 
			temp.push_back(num);	// add new number to row


		if ((column != -1) && temp.size() != column)		// for the first time column value is -1, so the if statement is false 
			matrix_check = false;						// it becomes the size of temp 
		column = temp.size();							// i ckecked the present row size (column) with previous one each time

		matrix.push_back(temp);		// add whole row to the matrix			
	}

	// checks if the matrix is in correct form and if all the integers are positive
	if (matrix_check == false)
		cout	<< "The matrix in the input file is not in correct matrix format or contains invalid elements. " << endl;
	

	// matrix is OK
	else
	{
		int row = matrix.size();

		cout	<< endl	<< endl
				<< "Please enter a sum value that will be searched in the matrix" << endl
				<< "(anything other than a positive integer to quit) : ";

		int sum;	// the sum value that user enters
		while (cin >> sum && sum > 0)	// loop continues if the input is positive integer (or it can be read as positive integer)
		{	
			// search(matrix, sum, row, column) searches for sum value in matrix and prints any matches, and returns total occurance 

			cout	<< "Total Occurance: " << search(matrix, sum, row, column) << endl << endl;

			cout	<< "Please enter a sum value that will be searched in the matrix" << endl
					<< "(anything other than a positive integer to quit) : ";
		}
	}

	cout	<< "End of execution." << endl << endl;

	inputFile.close();

	return 0;
}