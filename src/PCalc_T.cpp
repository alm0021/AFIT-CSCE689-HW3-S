#include <iostream>
#include <pthread.h>
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
	pthread_t threads[numOfThreads];
	// A value in primelist[i] will
	// finally be false if i is Not a prime, else true.

	for (unsigned int p = 2; p * p <= this->array_size(); p++)
	{
		if (this->at(p) == true)
		{
			for (unsigned int i = p * p; i <= this->array_size(); i += p)
				this->at(i) = false;
		}
	}
}