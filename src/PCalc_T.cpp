#include <iostream>
#include "PCalc_T.h"

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size) {}

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
	if (primelist != NULL)
		delete[] primelist;
	primelist = NULL;
}

/************************************************************************************************
 * markNonPrimes - 
 ************************************************************************************************/
void PCalc_T::markNonPrimes()
{
}