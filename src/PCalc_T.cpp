#include <iostream>
#include <cstring>
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
	memset(threadpos, 0, sizeof(unsigned int) * t_amt);
	std::thread threads[t_amt]; // threads array

	auto mark2 = [](PCalc_T *P, unsigned int &pos) { //lambda to pass to thread
		//Update multiples of pos greater than or equal to pos squared
		unsigned int p = pos;
		for (unsigned int i = pos * pos; i <= P->array_size(); i += p)
		{
			P->at(i) = false;
			pos = i;
		}
		pos = 0; // Tell the management thread we are done
	};

	//management thread
	unsigned int sqrt_n = sqrt(n);
	unsigned int lowest_thread = 3;
	for (unsigned int startPt = 2; startPt < sqrt_n; startPt++)
	{
		if (this->at(startPt) == true)
		{

			for (unsigned int i = 0; i < t_amt; i++) // loop through threads
			{
				if (threadpos[i] == 0) // thread is complete, launch a new thread
				{
					if (threads[i].joinable())
					{
						threads[i].join();
					}
					// find next position for new thread to start
					while (threadpos[i] >= lowest_thread) // Sleep if new start position is ahead of ahead of other threads
					{
						lowest_thread = findLow(threadpos);
						if (threadpos[i] >= lowest_thread)
						{
							std::this_thread::sleep_for(std::chrono::milliseconds(10));
						}
					}
					threadpos[i] = startPt;
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

	for (unsigned int i = 0; i < t_amt; i++)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
}

/************************************************************************************************
 * findLow - returns index of lowest position in threads
 ************************************************************************************************/
unsigned int PCalc_T::findLow(unsigned int *threadpos)
{
	unsigned int low = threadpos[0];
	for (unsigned int i = 1; i < t_amt; i++)
	{
		if ((threadpos[i] > 0) && (threadpos[i] < low))
		{
			low = threadpos[i];
		}
	}
	return low;
}