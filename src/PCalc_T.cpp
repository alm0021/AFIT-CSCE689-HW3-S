#include <iostream>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <math.h>
#include <chrono>
#include "PCalc_T.h"

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size)
{
	t_amt = num_threads;
}

/************************************************************************************************
 * PCalc_T (destructor) - deletes the primelist array
 ************************************************************************************************/
PCalc_T::~PCalc_T()
{
	cleanup();
}

/************************************************************************************************
 * cleanup - cleans up memory from this object
 ************************************************************************************************/
void PCalc_T::cleanup()
{
	this->PCalc::cleanup();
}

/************************************************************************************************
 * markNonPrimes - 
 ************************************************************************************************/
void PCalc_T::markNonPrimes()
{
	unsigned int n = this->array_size(); // size of arraylist
	unsigned int threadpos[t_amt];		 // int array to keep track of thread positions
	memset(threadpos, 0, sizeof(unsigned int)*t_amt);
	std::thread threads[t_amt];			 // threads array

	auto mark2 = [](PCalc_T *P, unsigned int &pos) { //lambda to pass to thread
		//Update multiples of pos >= pos^2
		unsigned int p = pos;
		for (unsigned int i = pos * pos; i <= P->array_size(); i += p)
		{
			P->at(i) = false;
			std::cout << i << " is not prime." << std::endl;
			pos = i;
		}
		
		pos = 0; // Tell the management thread we are done
		
	};

	//management thread
	for (unsigned int startPt = 2; startPt < sqrt(n); startPt++)
	{
		if (this->at(startPt) == true)
		{

			for (unsigned int i = 0; i < t_amt; i++) // loop through threads
			{
				if (threadpos[i] == 0) // thread is complete, launch a new thread
				{	
					if(threads[i].joinable()){
						threads[i].join();
					}
					// find next position for new thread to start
					// threadpos[i] = newStartPos();
					threadpos[i] = startPt;
					while (threadpos[i] < findLow(threadpos)) // Sleep if new start position is ahead of ahead of other threads
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(10));
					}
					std::cout << "Starting Thread with Pos: " << threadpos[i] << std::endl;
					threads[i] = std::thread(mark2, this, std::ref(threadpos[i]));
					break;
				}
				if (i == t_amt - 1)
				{
					i = 0;
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	//lambda function that marks non primes to pass to thread
	//splits into parts
	// auto segSieve = [this](unsigned int x) {
	// 	unsigned int n = this->array_size();								// size of array
	// 	unsigned int j = (x * (n / t_amt));									// upper bound of thread
	// 	unsigned int k = j - (n / t_amt - 1) < 2 ? 2 : j - (n / t_amt - 1); // where thread starts
	// 	if (k > 2)
	// 	{
	// 		for (unsigned int h = k; h < n / t_amt; h++)
	// 		{
	// 			if (this->at(h) == true)
	// 				k = h;
	// 			break;
	// 		}
	// 	}
	// 	std::cout << "Thread " << x << " starting prime is: " << k << std::endl;

	// 	for (unsigned int p = k; p * p <= j; p++)
	// 	{
	// 		if (this->at(p) == true)
	// 		{
	// 			for (unsigned int i = p * p; i <= j; i += p)
	// 				this->at(i) = false;
	// 		}
	// 	}
	// };

	// for (unsigned int i = 0; i < t_amt; i++)
	// {
	// 	threads[i] = std::thread(mark2, i);
	// }
	// for (unsigned int i = 0; i < t_amt; i++)
	// {
	// 	threads[i].join();
	// }
}

/************************************************************************************************
 * newStart - returns index of next prime for new thread
 ************************************************************************************************/
unsigned int PCalc_T::newStartPos()
{
	for (unsigned int i = 2; i < sizeof(this->array_size()); i++)
	{
		if (this->at(i) == true)
		std::cout << "New Start Position is " << i << std::endl;
			return i;
	}
	return 0;
}

/************************************************************************************************
 * findLow - returns index of lowest position in threads
 ************************************************************************************************/
unsigned int PCalc_T::findLow(unsigned int *threadpos)
{
	unsigned int low = threadpos[0];
	for (unsigned int i = 1; i < t_amt; i++)
	{
		if (threadpos[i] < low)
		{
			low = threadpos[i];
		}
	}
	return low;
}