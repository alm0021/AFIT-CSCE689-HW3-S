#include <iostream>
#include <bits/stdc++.h>
#include "PCalc_SP.h"

PCalc_SP::PCalc_SP(unsigned int ar_sz) : PCalc(ar_sz)
{
	asize = ar_sz;
	bool primes[asize];
	primelist = primes;
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
	if (primelist != NULL)
		delete[] primelist;
	primelist = NULL;
}

/************************************************************************************************
 * markNonPrimes - 
 ************************************************************************************************/
void PCalc_SP::markNonPrimes()
{
	// Create a boolean array "prime[0..n]" and initialize
	// all entries it as true. A value in prime[i] will
	// finally be false if i is Not a prime, else true.
	//primelist[n+1];
	memset(primelist, true, sizeof(primelist));

	for (int p = 2; p * p <= asize; p++)
	{
		// If prime[p] is not changed, then it is a prime
		if (primelist[p] == true)
		{
			// Update all multiples of p greater than or
			// equal to the square of it
			// numbers which are multiple of p and are
			// less than p^2 are already been marked.
			for (int i = p * p; i <= asize; i += p)
				primelist[i] = false;
		}
	}
}