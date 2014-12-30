#include "Histogram_16.h"

static void *parallel16_t(void *input) {
	int i;
	threads16_t *in = (threads16_t *) input;
	const int start = in->thread * in->size / NUM_THREADS;
	const int stop  = in->thread + 1 == NUM_THREADS ? in->size : (in->thread + 1) * in->size / NUM_THREADS;
	const int curr  = in->thread << 16;
	uint32_t *A     = &in->histA[curr];
	for (i=start;i<stop;++i)
		A[in->position(in->array[i])]++;
	pthread_exit(NULL);
}
void histogram16_t(uint16_t *array, uint32_t *histA, int size, uint16_t (*position)(uint16_t element)) {
	int i, j;
	pthread_t thread[NUM_THREADS];
	threads16_t *output    = (threads16_t *) calloc(NUM_THREADS, sizeof(threads16_t));
	for (i=0;i<NUM_THREADS;++i) {
		output[i].size     = size;
		output[i].thread   = i;
		output[i].array    = array;
		output[i].histA    = histA;
		output[i].position = position;
		pthread_create(&thread[i], NULL, parallel16_t, (void *) &output[i]);
	}
	for (i=0;i<NUM_THREADS;++i)
		pthread_join(thread[i], NULL);

	for (i=1;i<NUM_THREADS;++i) {
		int curr = i << 16;
		for (j=0;j<65536;++j)
			histA[j] += histA[curr + j];
	}
	for (i=1;i<65536;++i)
		histA[i] += histA[i-1];
	free(output);
}
