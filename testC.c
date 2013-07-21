#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "RadixSort.h"

typedef int types;
int main (int argc, char *argv[]) {
    const int size = atoi(argv[1]);
    srand(time(NULL));
	int i;
   
	types *array = malloc(size * sizeof(types));
	
	if (sizeof(types) == 1)
		for (i=0;i<size;i++) {
			uint8_t *temp = (uint8_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0f);
			if (rand() % 2) *temp |= 0x80;
		}
	else if (sizeof(types) == 2)
		for (i=0;i<size;i++) {
			uint16_t *temp = (uint16_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0fff);
			if (rand() % 2) *temp |= 0x8000;
		}
	else if (sizeof(types) == 4)
		for (i=0;i<size;i++) {
			uint32_t *temp = (uint32_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0fffffff);
			if (rand() % 2) *temp |= 0x80000000;
		}
	else if (sizeof(types) == 8)
		for (i=0;i<size;i++) {
			uint64_t *temp = (uint64_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0fffffffffffffff);
			if (rand() % 2) *temp |= 0x8000000000000000;
		}
		
	radixSort(RADIX_INT, &array[0], size);

    uint8_t sorted = 1;
    for (i=1;i<size;i++)
        if (array[i] < array[i-1]) {
            sorted = 0;
            break;
        }
    if (sorted) printf("Array sucessfully sorted!\n");
	else printf("Array was not sorted!\n");
	
	free(array);
    return 0;
}
