#ifndef _RADIXINCLUDES_H
#define _RADIXINCLUDES_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_THREADS 8
#define HIST_SIZE 2048
#define HIST_FULL NUM_THREADS * HIST_SIZE

#define _x1(x) (x & 0x7ff)
#define _x2(x) ((x >> 11) & 0x7ff)
#define _x3(x) ((x >> 22) & 0x7ff)
#define _x4(x) ((x >> 33) & 0x7ff)
#define _x5(x) ((x >> 44) & 0x7ff)
#define _x6(x) (x >> 55)

#endif
