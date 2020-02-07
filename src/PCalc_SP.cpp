 #include <iostream>

#include "PCalc_SP.h"

/************************************************************************************************
 * PCalc_SP (destructor) - deletes the primelist array
 ************************************************************************************************/

PCalc_SP::~PCalc_SP() {
	cleanup();
}

/************************************************************************************************
 * cleanup - cleans up memory from this object
 ************************************************************************************************/
void PCalc_SP::cleanup() {
	if (primelist != NULL)
		delete[] primelist;
	primelist = NULL;
}