#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "randgen.h"
#include "HW7IntQueue.h"

using namespace std;

mutex Mqueue1, Mqueue2, Mcout, Mcounter;	// for queues, cout and checkoutCounter

struct Time	{ int min, max; };	// there were too many arguments so that the program gave an error, therefore i used struct and reduced the parameter number by one 

// arrival of the customers
void arrival (int & ctr, int total, Time arrivalTime, HW7IntQueue & q1, HW7IntQueue & q2)
{
	while (ctr <= total)	// until the customers finish
	{
		// sleep for a random time between min and max
		RandGen random;
		int sleepTime = random.RandInt(arrivalTime.min, arrivalTime.max);
		this_thread::sleep_for(chrono::seconds(sleepTime));


		if		(q1.getQueueSize() < q2.getQueueSize())		// q1 has fewer people
		{
			Mqueue1.lock();		// locks q1
			q1.enqueue(ctr);	// enqueues customer to q1

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			Mcout.lock();
			cout << "Customer " << ctr << " has arrived at Cashier A's line (queue size is " << q1.getQueueSize() << "): " << put_time(ptm,"%X") << endl;
			Mcout.unlock();

			Mqueue1.unlock();	// unlocks q1
		}

		else if (q2.getQueueSize() < q1.getQueueSize())		//q2 has fewer people	
		{
			Mqueue2.lock();		// locks q2
			q2.enqueue(ctr);	// enqueus customer to q2

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			Mcout.lock();
			cout << "Customer " << ctr << " has arrived at Cashier B's line (queue size is " << q2.getQueueSize() << "): " << put_time(ptm,"%X") << endl;
			Mcout.unlock();

			Mqueue2.unlock();	// unlocks q2
		}

		
		else	// both have same number of people			
		{
			// q1 is not busy
			if		(Mqueue1.try_lock())
			{
				q1.enqueue(ctr);	// enqueues customer to q1

				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				Mcout.lock();
				cout << "Customer " << ctr << " has arrived at Cashier A's line (queue size is " << q1.getQueueSize() << "): " << put_time(ptm,"%X") << endl;
				Mcout.unlock();

				Mqueue1.unlock();	// unlocks q1
			}

			// q1 is busy, q2 is not busy
			else if (Mqueue2.try_lock())
			{
				q2.enqueue(ctr);	// enqueues customer to q2

				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				Mcout.lock();
				cout << "Customer " << ctr << " has arrived at Cashier B's line (queue size is " << q2.getQueueSize() << "): " << put_time(ptm,"%X") << endl;
				Mcout.unlock();

				Mqueue2.unlock();	// unlocks q2
			}

			// both are busy
			else
			{
				Mqueue1.lock();		// locks q1
				q1.enqueue(ctr);	// enqueues customer to q1

				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				Mcout.lock();
				cout << "Customer " << ctr << " has arrived at Cashier A's line (queue size is " << q1.getQueueSize() << "): " << put_time(ptm,"%X") << endl;
				Mcout.unlock();

				Mqueue1.unlock();	// unlocks q1
			}
		}

		ctr++;	// increases customer counter
	}

	return;
}

// checkout of the customers
void checkout (HW7IntQueue & queue, int queueNo, Time checkoutTime, int total, int & counter)
{
	char cashier;	// keeps 'A' or 'B'

	if (queueNo == 1)
		cashier = 'A';
	else
		cashier = 'B';

	int customerNo;	// keeps the number of customers checked out by both cashiers

	while (counter < total)	// while counter (total customers have finished checkout) is less than total customers that should checkout
	{
		// lock queue
		if (queueNo == 1)	Mqueue1.lock();
		else				Mqueue2.lock();

		if (!queue.isEmpty())	// queue is not empty
		{
			// dequeue customer
			queue.dequeue(customerNo);

			Mcounter.lock();
			counter++;			// increases customerCounter
			Mcounter.unlock();

			time_t tt1 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm1 = new struct tm; 
			localtime_s(ptm1, &tt1); 
			Mcout.lock();
			cout << "Cashier " << cashier << " has started transaction with customer " << customerNo << " (queue size is " << queue.getQueueSize() << "): " << put_time(ptm1,"%X") << endl;
			Mcout.unlock();

			// unlock queue			
			if (queueNo == 1)	Mqueue1.unlock();
			else				Mqueue2.unlock();

			// sleep for a random time between min and max
			RandGen random;
			int sleepTime = random.RandInt(checkoutTime.min, checkoutTime.max);
			this_thread::sleep_for(chrono::seconds(sleepTime));
		
			time_t tt2 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm2 = new struct tm; 
			localtime_s(ptm2, &tt2); 
			Mcout.lock();
			cout << "Cashier " << cashier << " finished transaction with customer " << customerNo << ": " << put_time(ptm2,"%X") << endl;
			Mcout.unlock();
		}

		else	// queue is empty
		{	
			// unlock queue
			if (queueNo == 1)	Mqueue1.unlock();
			else				Mqueue2.unlock();
		}
	}

	return;
}

int main()
{
	int totalCustomers;			// given by user
	int customerCounter = 1;	// counts arrivals
	int checkoutCounter = 0;	// counts checkouts
	
	Time arrivalTime;	// min and max time for arrival	(used struct because there were too many arguments so that the program gave an error)
	Time checkoutTime;	// min and max time for arrival 

	cout	<< "Please enter the total number of customers to be served: ";
	cin		>> totalCustomers;
	
	// creating queues and allocating capacity
	HW7IntQueue queue1;		queue1.allocateCapacity (totalCustomers - (totalCustomers / 2));
	HW7IntQueue queue2;		queue2.allocateCapacity (totalCustomers / 2);

	cout	<< endl << "Please enter the inter-arrival time range between two customers" << endl;
	cout	<< "min: ";
	cin		>> arrivalTime.min;
	cout	<< "max: ";
	cin		>> arrivalTime.max;

	cout	<< endl << "Please enter the checkout time range of cashiers" << endl;
	cout	<< "min: ";
	cin		>> checkoutTime.min;
	cout	<< "max: ";
	cin		>> checkoutTime.max;

	cout << endl << "--------------------------------------------------------------------------------";
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout << endl << "Simulation begins at " << put_time(ptm,"%X") << endl << endl;
	
	/****************************************************************************************************/

	// arrival
	thread Tenqueue(&arrival, ref(customerCounter), totalCustomers, arrivalTime, ref(queue1), ref(queue2));
	
	// checkouts
	thread Tdequeue1(checkout, ref(queue1), 1, checkoutTime, totalCustomers, ref(checkoutCounter));
	thread Tdequeue2(checkout, ref(queue2), 2, checkoutTime, totalCustomers, ref(checkoutCounter));

	// joins
	Tenqueue.join();
	Tdequeue1.join();
	Tdequeue2.join();

	/****************************************************************************************************/

	cout << endl << "Simulation ends" << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;


	return 0;
}