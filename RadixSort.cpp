#include "RadixSort.hpp"

// Copyright (C) 2013 by Kevin Melkowski, All Rights Reserved.

void RadixSort::sort (int *array, int size) {
	radixSortInt(array, size);
}
void RadixSort::sort (float *array, int size) {
	radixSortFloat(array, size);
}
void RadixSort::sort (double *array, int size) {
	radixSortDouble(array, size);
}