#include "RadixSort.hpp"

// Copyright (C) 2013 by Kevin Melkowski, All Rights Reserved.
void RadixSort::sort (char *array, int size) {
	uint32_t hist[256] = {0};
	uint8_t *temp      = new uint8_t[size]();
	uint8_t *input     = (uint8_t *) array;
	
	for (int i=0;i<size;i++)
		hist[input[i] ^ 0x80]++;
	for (int i=1;i<256;i++)
		hist[i] += hist[i-1];
	for (int i=size-1;i>=0;i--)
		temp[--hist[input[i] ^ 0x80]] = input[i];
		
	std::copy(temp, temp+size, input);
	delete[] temp;
}
void RadixSort::sort (short *array, int size) {
	radixSortShort(array, size);
}
void RadixSort::sort (int *array, int size) {
	radixSortInt(array, size);
}
void RadixSort::sort (float *array, int size) {
	radixSortFloat(array, size);
}
void RadixSort::sort (int64_t *array, int size) {
	radixSortint64_t(array, size);
}
void RadixSort::sort (double *array, int size) {
	radixSortDouble(array, size);
}
void RadixSort::sort (uint8_t *array, int size) {
	uint32_t hist[256] = {0};
	uint8_t *temp      = new uint8_t[size]();
	
	for (int i=0;i<size;i++)
		hist[array[i]]++;
	for (int i=1;i<256;i++)
		hist[i] += hist[i-1];
	for (int i=size-1;i>=0;i--)
		temp[--hist[array[i]]] = array[i];
		
	std::copy(temp, temp+size, array);
	delete[] temp;
}
void RadixSort::sort (uint16_t *array, int size) {
	radixSortuint16_t(array, size);
}
void RadixSort::sort (uint32_t *array, int size) {
	radixSortuint32_t(array, size);
}
void RadixSort::sort (uint64_t *array, int size) {
	radixSortuint64_t(array, size);
}