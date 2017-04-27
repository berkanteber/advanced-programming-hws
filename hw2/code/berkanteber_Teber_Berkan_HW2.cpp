/***********************************************************

Berkan Teber berkanteber 19080

************************************************************
HW2 -- constructing a movie database as linked lists
	-- modifying the list with various options

***********************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// movie is a node of the linked list
struct movie
{
	string movieName;
	int sumOfRatings;
	int totalVotes;

	movie* next;

	//Default Constructor (I used constructor with paramters, therefore i wrote a default constructor also.)
	movie :: movie () 
	{}

	//Constructor with parameters
	movie :: movie (string name, int rating, movie* p)
		: movieName(name) , sumOfRatings(rating) , totalVotes(1) , next(p)
	{}
};

void checkList(movie*&, string, int);	// updates the node if found; otherwise, inserts as a new node
void loadFromFile(movie*&);				// option 1 - loads the movies from a file
void addManually(movie*&);				// option 2 - adds the movie rating manually
void removeMovie(movie*&);				// option 3 - removes the movie from the list
void displayList(movie*);				// option 4 - displays the list
void deleteList(movie*);				// option 5 - deletes all the nodes before exit

int main()
{
	int choice;
	movie* head = NULL;

	do
	{
		cout	<< "Movie Rating System" << endl
				<< "-----------------------------------" << endl
				<< "Please select one option:" << endl
				<< "1. Load movie ratings from a file." << endl
				<< "2. Add a new rating manually." << endl
				<< "3. Remove an existing movie." << endl
				<< "4. Display the list of movies and rating information." << endl
				<< "5. Exit." << endl << endl
				<< "Your choice: ";

		while(!(cin >> choice))		// ignores non-integers
		{
			cin.clear();
			cin.ignore();
		}

		cout	<< endl;

		if		(choice == 1)
			loadFromFile(head);	// loads the movie from a file 
		else if (choice == 2)	
			addManually(head);	// adds the movie rating manually
		else if (choice == 3)
			removeMovie(head);	// removes the movie from the list
		else if (choice == 4)
			displayList(head);	// displays the list
		else if (choice == 5)
			deleteList(head);	// deletes all the nodes
		else																	// if it's an integer, but it's out of range
			cout << "Your choice must be in range 1 to 5." << endl << endl;

	} while (choice != 5); // loop continues until the exit command (5)

	return 0;
}

// updates the node if found; otherwise, inserts as a new node
void checkList(movie* &head, string name, int rating)
{
	if (head == NULL || name < head->movieName)		// empty list or the movie will be added as a new node to the beginning
	{
		head = new movie(name, rating, head);
		cout << name << " has been added to the list." << endl;
	}

	else if (name == head->movieName)				// first node matches with the movie, updates the values
	{
		head->sumOfRatings += rating;
		head->totalVotes ++;
		cout << name << " has been updated." << endl;	
	}

	else											// for the nodes other than the first
	{
		movie* ptr = head; 
		movie* prev;	// takes the previous node of ptr
		while(ptr != NULL && name >= ptr->movieName)		// continues until (i) the list ends (ii) reaches the place to be inserted (iii) reaches the node to be updated
		{
			prev = ptr;
			ptr = ptr->next;
		}

		if (name == prev->movieName) // updates the node if there is a match
		{
			prev->sumOfRatings += rating;
			prev->totalVotes ++;
			cout << name << " has been updated." << endl;
		}
		else						// inserts the movie as a new node
		{
			prev->next = new movie(name, rating, ptr);
			cout << name << " has been added to the list." << endl;
		}
	}

	return;
}

// loads the movie from a file
void loadFromFile(movie* &head)
{
	ifstream inputFile;
	string fileName;

	cout	<< "Please enter the name of the file: ";
	cin		>> fileName;

	// open input file
	inputFile.open(fileName.c_str());
	while (inputFile.fail())			// retake the file name until there is no problem
	{
		cout	<< "File cannot be opened." << endl
				<< "Please enter the name of the file again: " ;
		cin		>> fileName;

		inputFile.clear();
		inputFile.open(fileName.c_str());
	}

	cout << endl;

	string name;
	int rating;

	string line;
	while(getline(inputFile, line))
	{
		stringstream ss(line);

		ss >> name >> rating;
	
		if (rating >= 1 && rating <= 10)	// if rating is within the range
			checkList(head, name, rating);	// update or add/insert
		else
			cout << "The movie " << name << " does not have a valid rating." << endl;
	}

	cout << endl << "Movies from file " << fileName << " has been loaded." << endl << endl << endl;
	
	inputFile.close();
	return;
}

// adds the movie manually
void addManually(movie* &head)
{
	string name;
	int rating;

	cout	<< "Please enter the name of the movie you wish to rate: ";
	cin		>> name;
	cout	<< "Please enter the rating you wish to submit (1..10): ";
	cin		>> rating;

	cout << endl;

	if (rating >= 1 && rating <= 10)	// if rating is within the range
		checkList(head, name, rating);	// update or add insert
	else
		cout << "You have entered an invalid rating." << endl;

	cout << endl << endl;;

	return;
}

// removes the movie from the list
void removeMovie(movie* &head)
{
	string name;

	cout	<< "Please enter the name of the movie you wish to remove: ";
	cin		>> name;

	bool removed = false;	// if there is match and the movie is removed, boolean expression becomes true

	movie* ptr = head;

	if (head == NULL);					// means an empty list, does nothing (boolean is still false)

	else if (head->movieName == name)	// first movie matches, removes the movie
	{
		head = head->next;
		delete ptr;
		removed = true;
	}

	else								// movie is not empty and the first movie doesn't match
	{
		movie* prev = head;
		while (!removed && ptr->next != NULL)
		{
			ptr = ptr->next;
			if(ptr->movieName == name)	// there is a match, removes the movie
			{
				prev->next = ptr->next;
				delete ptr;
				removed = true;
			}
			prev = ptr;
		}
	}

	if (removed == true)	// there occured a match
		cout << endl << "The movie " << name << " has been removed from the list." << endl << endl;
	else					// there is no match
		cout << endl << "The movie " << name << " does not exist." << endl << endl;
	
	return;
}

// displays the list
void displayList(movie* head)
{
	if(head == NULL)	// list is empty
	{
		cout << "The movie list is empty." << endl;
	}
	
	else				// list is not empty, prints the list
	{
		movie* ptr = head;

		cout	<< setw(28) << left  << "Movie Name" << setw(22) << left << "Ratings Received" << setw(16) << left << "Avg. Rating" << endl
				<< "----------------------------------------------------------------" << endl;

		while(ptr!=NULL)
		{
			double averageRating = (double) ptr->sumOfRatings / ptr->totalVotes;
			cout << setw(32) << left << ptr->movieName << setw(20) << left << ptr->totalVotes << setw(16) << left <<  averageRating << endl;
	
			ptr = ptr->next;
		}
	}

	cout << endl << endl;

	return;
}

// deletes all the nodes
void deleteList(movie* ptr)
{
	if (ptr != NULL)
	{
		deleteList(ptr->next);
		delete ptr;
	}

	return;
}
