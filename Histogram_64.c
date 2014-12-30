#include "Histogram_64.h"

static void *parallel64_t(void *input) {
	int i;
	threads64_t *in = (threads64_t *) input;
	const int start = in->thread * in->size / NUM_THREADS;
	const int stop  = in->thread + 1 == NUM_THREADS ? in->size : (in->thread + 1) * in->size / NUM_THREADS;
	const int curr  = in->thread * HIST_SIZE;
	uint32_t *A     = &in->histA[curr];
	uint32_t *B     = &in->histB[curr];
	uint32_t *C     = &in->histC[curr];
	uint32_t *D     = &in->histD[curr];
	uint32_t *E     = &in->histE[curr];
	uint32_t *F     = &in->histF[curr];
	for (i=start;i<stop;++i) {
		const uint64_t pos = (in->array[i] = in->position(in->array[i]));
		A[_x1(pos)]++;
		B[_x2(pos)]++;
		C[_x3(pos)]++;
		D[_x4(pos)]++;
		E[_x5(pos)]++;
		F[_x6(pos)]++;
	}
	pthread_exit(NULL);
}
void histogram64_t(uint64_t *array, uint32_t *A, uint32_t *B, uint32_t *C, uint32_t *D, uint32_t *E, uint32_t *F, int size, uint64_t (*position)(uint64_t value)) {
	int i, j;
	pthread_t thread[NUM_THREADS];
	threads64_t *output    = (threads64_t *) calloc(NUM_THREADS, sizeof(threads64_t));
	for (i=0;i<NUM_THREADS;++i) {
		output[i].size     = size;
		output[i].thread   = i;
		output[i].array    = array;
		output[i].histA    = A;
		output[i].histB    = B;
		output[i].histC    = C;
		output[i].histD    = D;
		output[i].histE    = E;
		output[i].histF    = F;
		output[i].position = position;
		pthread_create(&thread[i], NULL, parallel64_t, (void *) &output[i]);
	}
	for (i=0;i<NUM_THREADS;++i)
		pthread_join(thread[i], NULL);

	for (i=1;i<NUM_THREADS;++i) {
		int curr = i * HIST_SIZE;
		for (j=0;j<HIST_SIZE;++j) {
			A[j] += A[curr + j];
			B[j] += B[curr + j];
			C[j] += C[curr + j];
			D[j] += D[curr + j];
			E[j] += E[curr + j];
			F[j] += F[curr + j];
		}
	}
	for (i=1;i<HIST_SIZE;++i) {
		A[i] += A[i-1];
		B[i] += B[i-1];
		C[i] += C[i-1];
		D[i] += D[i-1];
		E[i] += E[i-1];
		F[i] += F[i-1];
	}
	free(output);
}
