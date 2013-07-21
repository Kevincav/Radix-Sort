#include "RadixSortTypes.h"

// Copyright (C) 2013 by Kevin Melkowski, All Rights Reserved.

void radixSortShort(short *array, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(NUM_THREADS << 16, sizeof(uint32_t));
	uint16_t *temp  = (uint16_t *) malloc(size * sizeof(uint16_t));
	if (!histA || !temp) {
		if (histA) free(histA);
		if (temp) free(temp);
		return;
	}
	uint16_t *input = (uint16_t *) array;

	histogram16_t(input, histA, size, pos_int16_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[pos_int16_t(input[i])]] = input[i];

#pragma omp parallel for
	for (i=0;i<size;i++)
		input[i] = temp[i];
	
	free(histA);
	free(temp);
}
void radixSortuint16_t(uint16_t *array, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(NUM_THREADS << 16, sizeof(uint32_t));
	uint16_t *temp  = (uint16_t *) malloc(size * sizeof(uint16_t));
	if (!histA || !temp) {
		if (histA) free(histA);
		if (temp) free(temp);
		return;
	}

	histogram16_t(array, histA, size, pos_uint16_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[array[i]]] = array[i];

#pragma omp parallel for
	for (i=0;i<size;i++)
		array[i] = temp[i];
	
	free(histA);
	free(temp);
}

void radixSortInt(int *array, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histB = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histC = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *temp  = (uint32_t *) malloc(size * sizeof(uint32_t));
	uint32_t *input = (uint32_t *) array;
	if (!histA || !histB || !histC || !temp) {
		if (histA) free(histA);
		if (histB) free(histB);
		if (histC) free(histC);
		if (temp) free(temp);
		return;
	}

	histogram32_t(input, histA, histB, histC, size, pos_int32_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[_x1(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histB[_x2(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histC[_x3(input[i])]] = input[i];

#pragma omp parallel for
	for (i=0;i<size;i++)
		input[i] = pos_int32_t(temp[i]);
	
	free(histA);
	free(histB);
	free(histC);
	free(temp);
}
void radixSortuint32_t(uint32_t *array, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histB = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histC = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *temp  = (uint32_t *) malloc(size * sizeof(uint32_t));
	if (!histA || !histB || !histC || !temp) {
		if (histA) free(histA);
		if (histB) free(histB);
		if (histC) free(histC);
		if (temp) free(temp);
		return;
	}

	histogram32_t(array, histA, histB, histC, size, pos_uint32_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[_x1(array[i])]] = array[i];
	for (i=size-1;i>=0;--i)
		array[--histB[_x2(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histC[_x3(array[i])]] = array[i];

#pragma omp parallel for
	for (i=0;i<size;i++)
		array[i] = temp[i];
	
	free(histA);
	free(histB);
	free(histC);
	free(temp);
}

void radixSortFloat(float *array, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histB = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histC = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *temp  = (uint32_t *) malloc(size * sizeof(uint32_t));
	uint32_t *input = (uint32_t *) array;
	if (!histA || !histB || !histC || !temp) {
		if (histA) free(histA);
		if (histB) free(histB);
		if (histC) free(histC);
		if (temp) free(temp);
		return;
	}
	
	histogram32_t(input, histA, histB, histC, size, forwardf32_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[_x1(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histB[_x2(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histC[_x3(input[i])]] = input[i];
		
#pragma omp parallel for
	for (i=0;i<size;i++)
		input[i] = backf32_t(temp[i]);

	free(histA);
	free(histB);
	free(histC);		
	free(temp);
}

void radixSortDouble(double *array, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histB = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histC = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histD = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histE = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histF = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint64_t *temp  = (uint64_t *) malloc(size * sizeof(uint64_t));
	uint64_t *input = (uint64_t *) array;
	if (!histA || !histB || !histC || !histD || !histE || !histF || !temp) {
		if (histA) free(histA);
		if (histB) free(histB);
		if (histC) free(histC);
		if (histD) free(histD);
		if (histE) free(histE);
		if (histF) free(histF);
		if (temp) free(temp);
		return;
	}
	
	histogram64_t(input, histA, histB, histC, histD, histE, histF, size, forwardf64_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[_x1(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histB[_x2(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histC[_x3(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histD[_x4(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histE[_x5(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histF[_x6(temp[i])]] = backf64_t(temp[i]);

	free(histA);
	free(histB);
	free(histC);		
	free(histD);
	free(histE);
	free(histF);
	free(temp);
}
void radixSortint64_t(int64_t *array, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histB = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histC = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histD = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histE = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histF = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint64_t *temp  = (uint64_t *) malloc(size * sizeof(uint64_t));
	uint64_t *input = (uint64_t *) array;
	if (!histA || !histB || !histC || !histD || !histE || !histF || !temp) {
		if (histA) free(histA);
		if (histB) free(histB);
		if (histC) free(histC);
		if (histD) free(histD);
		if (histE) free(histE);
		if (histF) free(histF);
		if (temp) free(temp);
		return;
	}
	
	histogram64_t(input, histA, histB, histC, histD, histE, histF, size, pos_int64_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[_x1(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histB[_x2(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histC[_x3(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histD[_x4(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histE[_x5(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histF[_x6(temp[i])]] = pos_int64_t(temp[i]);

	free(histA);
	free(histB);
	free(histC);		
	free(histD);
	free(histE);
	free(histF);
	free(temp);
}
void radixSortuint64_t(uint64_t *input, int size) {
	int i;
	uint32_t *histA = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histB = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histC = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histD = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histE = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint32_t *histF = (uint32_t *) calloc(HIST_FULL, sizeof(uint32_t));
	uint64_t *temp  = (uint64_t *) malloc(size * sizeof(uint64_t));
	if (!histA || !histB || !histC || !histD || !histE || !histF || !temp) {
		if (histA) free(histA);
		if (histB) free(histB);
		if (histC) free(histC);
		if (histD) free(histD);
		if (histE) free(histE);
		if (histF) free(histF);
		if (temp) free(temp);
		return;
	}
	
	histogram64_t(input, histA, histB, histC, histD, histE, histF, size, pos_uint64_t);
	
	for (i=size-1;i>=0;--i)
		temp[--histA[_x1(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histB[_x2(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histC[_x3(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histD[_x4(temp[i])]] = temp[i];
	for (i=size-1;i>=0;--i)
		temp[--histE[_x5(input[i])]] = input[i];
	for (i=size-1;i>=0;--i)
		input[--histF[_x6(temp[i])]] = temp[i];

	free(histA);
	free(histB);
	free(histC);		
	free(histD);
	free(histE);
	free(histF);
	free(temp);
}