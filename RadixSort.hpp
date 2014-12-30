#ifndef _RADIXSORT_HPP
#define _RADIXSORT_HPP

#include <iostream>

#include "RadixSortTypes.h"

extern "C" {
	// Signed Sorts.
	void radixSortShort(short *array, int size);
	void radixSortInt(int *array, int size);
	void radixSortFloat(float *array, int size);
	void radixSortint64_t(int64_t *array, int size);
	void radixSortDouble(double *array, int size);

	// Unsigned Sorts.
	void radixSortuint16_t(uint16_t *array, int size);
	void radixSortuint32_t(uint32_t *array, int size);
	void radixSortuint64_t(uint64_t *array, int size);
}

class RadixSort {
	public:
		// Signed
		static void sort (char *array, int size);
		static void sort (short *array, int size);
		static void sort (int *array, int size);
		static void sort (float *array, int size);
		static void sort (int64_t *array, int size);
		static void sort (double *array, int size);
		
		// Unsigned
		static void sort (bool *array, int size);
		static void sort (uint8_t *array, int size);
		static void sort (uint16_t *array, int size);
		static void sort (uint32_t *array, int size);
		static void sort (uint64_t *array, int size);
};

#endif
