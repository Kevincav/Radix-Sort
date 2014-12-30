#ifndef _HISTOGRAM_64_H
#define _HISTOGRAM_64_H

#include <pthread.h>
#include "RadixIncludes.h"

typedef struct {
	int size, thread;
	uint64_t *array;
	uint32_t *histA, *histB, *histC, *histD, *histE, *histF;
	uint64_t (*position)(uint64_t value);
} threads64_t;

static inline uint64_t forwardf64_t(uint64_t number) {
    if (number >> 63) return number ^ 0xffffffffffffffff;
    return number ^ 0x8000000000000000;
}
static inline uint64_t backf64_t(uint64_t number) {
    if (number >> 63) return number ^ 0x8000000000000000;
    return number ^ 0xffffffffffffffff;
}
static inline uint64_t pos_int64_t(uint64_t number) {
    return number ^ 0x8000000000000000;
}
static inline uint64_t pos_uint64_t(uint64_t number) {
    return number;
}

void histogram64_t(uint64_t *array, uint32_t *A, uint32_t *B, uint32_t *C, uint32_t *D, uint32_t *E, uint32_t *F, int size, uint64_t (*position)(uint64_t value));

#endif
