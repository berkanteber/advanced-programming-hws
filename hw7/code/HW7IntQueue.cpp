#include <iostream>
#include "HW7IntQueue.h"
using namespace std;

HW7IntQueue::HW7IntQueue()
{
	queueArray = NULL;
}

HW7IntQueue::~HW7IntQueue()
{
	delete[] queueArray;
	queueArray = NULL;
}

HW7IntQueue::HW7IntQueue(HW7IntQueue &copyQueue)
{
	queueArray = new int[copyQueue.queueSize];
	queueSize = copyQueue.queueSize;
	for(int i = 0; i < queueSize; i++)
	{
		queueArray[i] = copyQueue.queueArray[i];
	}
}

const HW7IntQueue & HW7IntQueue::operator=(const HW7IntQueue & rhs)
{
	if(this != &rhs)
	{
		clear();
		queueArray = new int[rhs.queueSize];
		queueSize = rhs.queueSize;
		for(int i = 0; i < queueSize; i++)
		{
			queueArray[i] = rhs.queueArray[i];
		}
	}
	return *this;
}

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************
void HW7IntQueue::allocateCapacity(int s)
{
	queueArray = new int[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void HW7IntQueue::enqueue(int num)
{
	if (isFull())
    { 
         cout << "The queue is full. " << num << " not enqueued. Exiting program abnormally...\n";
		 exit(1);
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear] = num;
		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void HW7IntQueue::dequeue(int &num)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program abnormally...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		num = queueArray[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool HW7IntQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool HW7IntQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void HW7IntQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}

//*******************************************
// Function count returns the number of     *
// elements that are currently in the queue *
//*******************************************
int HW7IntQueue::getQueueSize()
{
	return numItems;
}