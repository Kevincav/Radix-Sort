#ifndef _RADIXSORT_H
#define _RADIXSORT_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "RadixSortTypes.h"

enum SortMethod {
	RADIX_CHAR,
	RADIX_SHORT,
	RADIX_INT,
	RADIX_LONG,
	RADIX_FLOAT,
	RADIX_DOUBLE,
	RADIX_LONG_LONG_INT,
	RADIX_UNSIGNED_CHAR,
	RADIX_UNSIGNED_SHORT,
	RADIX_UNSIGNED_INT,
	RADIX_UNSIGNED_LONG,
	RADIX_UNSIGNED_LONG_LONG_INT
};

extern void radixSortShort(short *array, int size);
extern void radixSortInt(int *array, int size);
extern void radixSortFloat(float *array, int size);
extern void radixSortDouble(double *array, int size);
extern void radixSortint64_t(int64_t *array, int size);
extern void radixSortuint16_t(uint16_t *array, int size);
extern void radixSortuint32_t(uint32_t *array, int size);
extern void radixSortuint64_t(uint64_t *array, int size);

void radixSort(enum SortMethod type, void *array, int size);

#endif