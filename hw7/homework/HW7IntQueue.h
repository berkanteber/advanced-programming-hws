#ifndef HW7INTQUEUE_H
#define HW7INTQUEUE_H

class HW7IntQueue
{
private:
	int *queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	HW7IntQueue();  //default constructor
	HW7IntQueue(HW7IntQueue&); // deep copy constructor
	~HW7IntQueue(); // destructor
	void allocateCapacity(int); //creates a static queue with given size
  	void enqueue(int); 
  	void dequeue(int &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
	int getQueueSize();

	const HW7IntQueue & HW7IntQueue::operator = (const HW7IntQueue & rhs);
};
#endif