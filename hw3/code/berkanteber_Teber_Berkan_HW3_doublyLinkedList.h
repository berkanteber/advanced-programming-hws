#ifndef _BERKANTEBER_TEBER_BERKAN_HW3_DOUBLYLINKEDLIST_H
#define _BERKANTEBER_TEBER_BERKAN_HW3_DOUBLYLINKEDLIST_H

#include <string>
using namespace std;

struct node
{
	string word;
	int count;
	node *next;			//forward direction
	node *previous;		//backward direction

	// default constructor
	node::node()
	{}

	// constructor
	node::node(const string &s, node * previousNode, node * nextNode)
		: word(s), count(1), previous(previousNode), next(nextNode)
	{}
};


class wordlist
{
	private:
		node *head;		// head node, start of wordlist
		node *tail;		// tail node, end of wordlist

	public:
		wordlist();					// constructor
		void AddWord(string);		// adds the word to the wordlist
		void RemoveWord(string);	// removes the word from the wordlist
		void SearchWord(string);	// searches for the word in the wordlist
		void PrintList();			// prints the wordlist (in alphabetical order)
		void ReversePrintList();	// prints the wordlist (in reverse alphabetical order)
		void DeleteList();			// deletes the wordlist
		bool isEmpty();				// checks if the wordlist is empty
};

#endif