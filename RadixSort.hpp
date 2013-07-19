#ifndef _RADIXSORT_HPP
#define _RADIXSORT_HPP

// Copyright (C) 2013 by Kevin Melkowski, All Rights Reserved.

#include "RadixSortTypes.h"

extern "C" void radixSortInt(int *array, int data);
extern "C" void radixSortFloat(float *array, int data);
extern "C" void radixSortDouble(double *array, int data);

class RadixSort {
	public:
		static void sort (int *array, int size);
		static void sort (float *array, int size);
		static void sort (double *array, int size);
};

#endif