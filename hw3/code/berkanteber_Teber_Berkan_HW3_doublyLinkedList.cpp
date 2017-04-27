#include <iostream>
#include "berkanteber_Teber_Berkan_HW3_doublyLinkedList.h"

using namespace std;


// constructor
wordlist::wordlist()
{
	head = NULL;	// head is NULL in the beginning
	tail = NULL;	// tail is NULL in the beginning
}

// adds the word to the wordlist
void wordlist::AddWord(string word)
{
	if (head == NULL)			// empty list
	{
		head = new node (word, NULL, NULL);
		tail = head;
	}

	else if (word < head->word)	// word must be inserted to the beginning
	{
		head = new node (word, NULL, head);
		
		if(head->next != NULL)
			head->next->previous = head;
	}

	else
	{
		node* ptr = head;

		while(word >= ptr->word && ptr!=tail)
			ptr = ptr->next;

		if (ptr == tail && ptr->word == word)		// word matches with the last word
		{	
			ptr->count++;
		}	
		else if (ptr == tail && word > ptr->word)	// word must be inserted to the end
		{
				ptr->next = new node (word, ptr, NULL);
				tail = ptr->next;		
		}
		else if (word == ptr->previous->word)		// word matches with the previous word
		{
			ptr->previous->count++;
		}
		else										// word must be inserted before ptr		
		{
			ptr->previous->next = new node (word, ptr->previous, ptr);
			ptr->previous = ptr->previous->next;
		}
	}
	
	return;
}

// removes the word from the wordlist
void wordlist::RemoveWord(string word)
{
	bool removed = false;	// checks if the word is removed
	node* ptr = head;
	while (!removed && ptr != NULL && word >= ptr->word)
	{
		if (word == ptr->word)	// there is a match
		{
			if (ptr != head)	
				ptr->previous->next = ptr->next;
			else				// matches with the first word
				head = ptr->next;
			
			if (ptr != tail )
				ptr->next->previous = ptr->previous;
			else				// matches with the last word
				tail = ptr->previous;

			delete ptr;
			removed = true;

			cout << word << " has been deleted" << endl << endl;
		}

		ptr = ptr->next;
	}

	if (!removed)	// there is no match
		cout << word << " does not exist." << endl << endl;

	return;
}

// searches for the word in the wordlist
void wordlist::SearchWord(string word)
{
	bool matched = false;
	node* ptr = head;
	while (!matched && ptr != NULL && word >= ptr->word)
	{
		if (word == ptr->word)	// there is match
		{
			cout << ptr->word << " " << ptr->count << endl;
			matched = true;
		}

		ptr = ptr->next;
	}

	if (!matched)	// there is no match
		cout << word << " does not exist." << endl;

	cout << endl;

	return;
}

// prints the wordlist (in alphabetical order)
void wordlist::PrintList()
{
	node* ptr = head;	// starts from the beginning

	while (ptr != NULL)	// until the end
	{
		cout << ptr->word << " " << ptr->count << endl;
	
		ptr = ptr->next;		// in alphabetical order
	}

	return;
}

// prints the wordlist (in reverse alphabetical order)
void wordlist::ReversePrintList() 
{
	node* ptr = tail;	// starts from the end

	while (ptr != NULL)	// until the beginning
	{
		cout << ptr->word << " " << ptr->count << endl;
	
		ptr = ptr->previous;		// in reverse alphabetical order
	}

	return;
}

// deletes the wordlist
void wordlist::DeleteList()
{
	node* ptr = head;	// starts from the beginning
	node* temp = ptr;

	while (ptr != NULL)	// until the end
	{
		temp = ptr;
		ptr = ptr->next;	
		delete temp;
	}

	return;
}

// checks if the wordlist is empty
bool wordlist::isEmpty()
{
	if (tail == NULL)	// empty list
		return true;
	else
		return false;
}