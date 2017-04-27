#include <iostream>
#include "berkanteber_Teber_Berkan_HW4_stack.h"

using namespace std;


// constructor
Stack::Stack ()
{
	top = NULL;
}
// pushes the node consisting the coordinates to the stack
void Stack::push (int x, int y)
{
	Node* newNode = new Node (x, y, top);	// creates a new node to the beginning
	top = newNode;							// top shows the new node
}

// pops the node and returns the coodinate values by reference
void Stack::pop (int &x, int &y)
{
	Node* temp;

	if (!isEmpty()) // only works when the stack is not empty
	{
		x = top -> x;	// x coordinate is extracted
		y = top -> y;	// y coordinate is extracted
	
		temp = top -> next;
		delete top;		// deletes the node
		top = temp;	
	}
}

// true if empty, false if not
bool Stack::isEmpty()
{
	if (top == NULL)
		return true;
	else
		return false;
}