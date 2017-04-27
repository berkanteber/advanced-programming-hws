/************************************************************

Berkan Teber berkanteber 19080

*************************************************************

This program takes an input and stores the count of every word.
	-- Words are categorized by letter and stored in a doubly linked list.
	-- Doubly linked lists are stored in a dynamic array.

Then, the program searches/removes a word, or print (a letter/ all letters) in (alphabetical/reverse alphabetical order).

************************************************************/


#include <iostream>
#include <fstream>
#include <sstream> 
#include "strutils.h"
#include "berkanteber_Teber_Berkan_HW3_doublyLinkedList.h"

using namespace std;

void addList (wordlist*&);	// takes the input file and creates the wordlists for each letter


int main()
{	
	wordlist* myWords = new wordlist [26];	// a wordlist for each letter

	addList (myWords);	// takes the input file and creates the wordlists for each letter

	int choice;

	do
	{
		cout	<< "--------------------------------------------------------------" << endl
				<< "Please select one option:" << endl
				<< "1. Display the count of a specific word" << endl
				<< "2. Remove a specific word" << endl
				<< "3. Display the words with the same initial letter (in alphabetical order)" << endl
				<< "4. Display the words with the same initial letter (in reverse alphabetical order)" << endl
				<< "5. Display all words (in alphabetical order)" << endl
				<< "6. Display all words (in reverse alphabetical order)" << endl
				<< "7. Exit" << endl << endl
				<< "Your choice: ";
				
		while (!(cin >> choice))		// ignores non-integers
		{
			cin.clear();
			cin.ignore();
		}
		
		cout << endl;

		if		(choice == 1)	// display the count of a specific word
		{
			cout << "Please enter a word to find out its count: ";
			string word;
			cin >> word;
			StripPunc (word);
			ToLower (word);
			cout << "******************************************" << endl;

			if (word[0] >= 'a' && word[0] <= 'z')	// first letter is OK
				myWords[word[0]- 'a'].SearchWord(word);
			else
				cout << "The word contains an invalid first letter." << endl << endl;
		}

		else if (choice == 2)	// remove a specific word
		{
			cout << "Please enter a word to remove: ";
			string word;
			cin >> word;
			StripPunc (word);
			ToLower (word);
			cout << "******************************************" << endl;

			if (word[0] >= 'a' && word[0] <= 'z')	// first letter is OK
				myWords[word[0]- 'a'].RemoveWord(word);
			else
				cout << "The word contains an invalid first letter." << endl << endl;
		}

		else if (choice == 3)	// display the words with the same initial letter (in alphabetical order)
		{
			cout << "Please enter a letter: ";
			string word;
			cin >> word;
			ToLower (word);
				
			cout << "******************************************" << endl;

			if (word.length() != 1 || !(word[0] >= 'a' && word[0] <= 'z')) // checks if there is only 1 character and that character is a letter 
				cout << word << " is not a letter." << endl << endl;
			else
			{
				if (myWords[word[0] - 'a'].isEmpty())	// no words starting with that letter
					cout << "There are no words starting with '" << word[0] << "'." << endl;
				else
					myWords[word[0] - 'a'].PrintList();
				
				cout << endl;
			}
		}
		
		else if (choice == 4)	// display the words with the same initial letter (in reverse alphabetical order)
		{
			cout << "Please enter a letter: ";
			string word;
			cin >> word;
			ToLower (word);

			cout << "******************************************" << endl;

			if (word.length() != 1 || !(word[0] >= 'a' && word[0] <= 'z')) // checks if there is only 1 character and that character is a letter 
				cout << "It is not a letter." << endl << endl;
			else
			{
				ToLower(word);

				if (myWords[word[0] - 'a'].isEmpty())	// no words starting with that letter
					cout << "There are no words starting with '" << word[0] << "'." << endl;
				else
					myWords[word[0] - 'a'].ReversePrintList();
				
				cout << endl;
			}
		}
		
		else if (choice == 5)	// display all words (in alphabetical order)
		{
			cout << "******************************************" << endl;

			bool empty = true;	// checks if there are any words
			
			for (int i = 0; i <= 25; i++)	// starts from the beginning
			{
				if (empty && !myWords[i].isEmpty()) // there is at least 1 word
					empty = false;

				myWords[i].PrintList();	// prints wordlist of the letter in alphabetical order
			}
			
			if (empty)	// no words in any letter
				cout << "There are no words." << endl;
			cout << endl;
		}
		
		else if (choice == 6)	// display all words (in reverse alphabetical order)
		{
			cout << "******************************************" << endl;

			bool empty = true;	// checks if there are any words
			
			for (int i = 25; i >= 0; i--)	// starts from the end
			{
				if (empty && !myWords[i].isEmpty())	// there is at least one word
					empty = false;

				myWords[i].ReversePrintList();	// prints wordlist of the letter in reverse alphabetical order
			}

			if (empty)	// no words in any letter
				cout << "There are no words.";
			cout << endl;
		}
		
		else if (choice == 7)	// exit
		{
			for (int i = 0; i <= 25; i++)
				myWords[i].DeleteList();	// deletes the wordlist of the letter
			
			delete [] myWords;	// deletes the dynamic array consists 1 wordlist for each letter 
		}
	} while (choice != 7); // loop continues until the exit command (7)

	return 0;
}

void addList(wordlist* &myWords)
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

	cout << endl;

	string word;
	while (inputFile >> word)
	{
		StripPunc (word);
		ToLower (word);

		if (word[0] >= 'a' && word[0] <= 'z')	// first letter is OK
			myWords[word[0]-'a'].AddWord(word);
		else
			cout << word << " cannot be added." << endl;
	}

	cout << "File " << fileName << " has been read and processed." << endl << endl;

	inputFile.close();

	return;
}