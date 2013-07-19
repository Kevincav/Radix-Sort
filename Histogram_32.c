#include "Histogram_32.h"

// Copyright (C) 2013 by Kevin Melkowski, All Rights Reserved.

static void *parallel32_t(void *input) {
	int i;
	threads32_t *in = (threads32_t *) input;
	const int start = in->thread * in->size / NUM_THREADS;
	const int stop  = in->thread + 1 == NUM_THREADS ? in->size : (in->thread + 1) * in->size / NUM_THREADS;
	const int curr  = in->thread * HIST_SIZE;
	uint32_t *A     = &in->histA[curr];
	uint32_t *B     = &in->histB[curr];
	uint32_t *C     = &in->histC[curr];
	for (i=start;i<stop;++i) {
		const uint32_t pos = (in->array[i] = in->position(in->array[i]));
		A[_x1(pos)]++;
		B[_x2(pos)]++;
		C[_x3(pos)]++;
	}
	pthread_exit(NULL);
}
void histogram32_t(uint32_t *array, uint32_t *histA, uint32_t *histB, uint32_t *histC, int size, uint32_t (*position)(uint32_t element)) {
	int i, j;
	pthread_t thread[NUM_THREADS];
	threads32_t *output    = (threads32_t *) calloc(NUM_THREADS, sizeof(threads32_t));
	for (i=0;i<NUM_THREADS;++i) {
		output[i].size     = size;
		output[i].thread   = i;
		output[i].array    = array;
		output[i].histA    = histA;
		output[i].histB    = histB;
		output[i].histC    = histC;
		output[i].position = position;
		pthread_create(&thread[i], NULL, parallel32_t, (void *) &output[i]);
	}
	for (i=0;i<NUM_THREADS;++i)
		pthread_join(thread[i], NULL);

	for (i=1;i<NUM_THREADS;++i) {
		int curr = i * HIST_SIZE;
		for (j=0;j<HIST_SIZE;++j) {
			histA[j] += histA[curr + j];
			histB[j] += histB[curr + j];
			histC[j] += histC[curr + j];
		}
	}
	for (i=1;i<HIST_SIZE;++i)
		histA[i] += histA[i-1];
	for (i=1;i<HIST_SIZE;++i)
		histB[i] += histB[i-1];
	for (i=1;i<HIST_SIZE;++i)
		histC[i] += histC[i-1];
	free(output);
}
