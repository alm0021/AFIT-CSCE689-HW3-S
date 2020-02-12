#include <iostream>
#include <pthread.h>
#include <thread>
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
	//lambda function that marks non primes to pass to thread
	auto markPrime = [this](int x) {
		unsigned int n = this->array_size();
		unsigned int k = (x * (n / t_amt)) - (n / t_amt - 1) < 2 ? 2 : (x * (n / t_amt)) - (n / t_amt - 1);
		if (k > 2)
		{
			for (int h = k; h < n / t_amt; h++)
			{
				if (this->at(h) == true)
					k = h;
				break;
			}
		}
		std::cout << "Thread " << x << " starting prime is: " << k << std::endl;
		unsigned int j = (x * (n / t_amt));
		for (unsigned int p = k; p * p <= j; p++)
		{
			if (this->at(p) == true)
			{
				for (unsigned int i = p * p; i <= j; i += p)
					this->at(i) = false;
			}
		}
	};

	// Create threads
	std::thread threads[t_amt];

	for (unsigned int i = 0; i < t_amt; i++)
	{
		threads[i] = std::thread(markPrime, i);
	}
	for (unsigned int i = 0; i < t_amt; i++)
	{
		threads[i].join();
	}
}

void PCalc_T::markPrimeThread(unsigned int prime)
{
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