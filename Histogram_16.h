#ifndef _HISTOGRAM_16_H
#define _HISTOGRAM_16_H

// Copyright (C) 2013 by Kevin Melkowski, All Rights Reserved.

#include <pthread.h>
#include "RadixIncludes.h"

typedef struct {
	int size, thread;
	uint16_t *array;
	uint32_t *histA;
	uint16_t (*position)(uint16_t element);
} threads16_t;


static inline uint16_t pos_int16_t(uint16_t number) {
    return number ^ 0x8000;
}
static inline uint16_t pos_uint16_t(uint16_t number) {
    return number;
}

void histogram16_t(uint16_t *array, uint32_t *histA, int size, uint16_t (*position)(uint16_t element));

#endif