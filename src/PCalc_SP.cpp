// https://www.geeksforgeeks.org/sieve-of-eratosthenes/

#include <iostream>
#include <bits/stdc++.h>
#include "PCalc_SP.h"

PCalc_SP::PCalc_SP(unsigned int ar_sz) : PCalc(ar_sz)
{
}

/************************************************************************************************
 * PCalc_SP (destructor) - deletes the primelist array
 ************************************************************************************************/
PCalc_SP::~PCalc_SP()
{
	cleanup();
}

/************************************************************************************************
 * cleanup - cleans up memory from this object
 ************************************************************************************************/
void PCalc_SP::cleanup()
{
	this->PCalc::cleanup();
}

/************************************************************************************************
 * markNonPrimes - 
 ************************************************************************************************/
void PCalc_SP::markNonPrimes()
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