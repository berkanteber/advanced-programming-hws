#ifndef _BERKANTEBER_TEBER_BERKAN_HW4_STACK_H
#define _BERKANTEBER_TEBER_BERKAN_HW4_STACK_H


// node struct for stack implementation
struct Node
{
	int x, y;
	Node* next;

	// default Constructor
	Node::Node ()
	{}

	// constructor
	Node::Node (int xCoord, int yCoord, Node* nextNode)
		: x (xCoord) , y (yCoord) , next (nextNode)
	{}
};

// stack class
class Stack
{
private:
		Node* top;					// shows the top element

public:
		Stack ();					// constructor
		void push (int, int);		// pushes the node consisting the coordinates to the stack
		void pop (int &, int &);	// pops the node and returns the coodinate values by reference
		bool isEmpty ();			// true if empty, false if not
};

#endif