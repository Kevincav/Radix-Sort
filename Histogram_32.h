#ifndef _HISTOGRAM_32_H
#define _HISTOGRAM_32_H

#include <pthread.h>
#include "RadixIncludes.h"

typedef struct {
	int size, thread;
	uint32_t *array;
	uint32_t *histA, *histB, *histC;
	uint32_t (*position)(uint32_t element);
} threads32_t;

static inline uint32_t forwardf32_t(uint32_t number) {
    if (number >> 31) return number ^ 0xffffffff;
    return number ^ 0x80000000;
}
static inline uint32_t backf32_t(uint32_t number) {
    if (number >> 31) return number ^ 0x80000000;
    return number ^ 0xffffffff;
}
static inline uint32_t pos_int32_t(uint32_t number) {
    return number ^ 0x80000000;
}
static inline uint32_t pos_uint32_t(uint32_t number) {
    return number;
}

void histogram32_t(uint32_t *array, uint32_t *histA, uint32_t *histB, uint32_t *histC, int size, uint32_t (*position)(uint32_t element));

#endif
