#include "RadixSort.h"

void radixSort (enum SortMethod type, void *array, int size) {
	int i;
	switch (type) {
		case RADIX_CHAR: {
			uint32_t hist[256] = {0};
			uint8_t *temp      = malloc(size * sizeof(uint8_t));
			uint8_t *input     = (uint8_t *) array;
			
			for (i=0;i<size;i++)
				hist[input[i] ^ 0x80]++;
			for (i=1;i<256;i++)
				hist[i] += hist[i-1];
			for (i=size-1;i>=0;i--)
				temp[--hist[input[i] ^ 0x80]] = input[i];
				
			memcpy(input, temp, size * sizeof(uint8_t));
			free(temp);
		}
			break;
		case RADIX_SHORT:
			radixSortShort((short *) array, size);
			break;
		case RADIX_INT:
		case RADIX_LONG:
			radixSortInt((int *) array, size);
			break;
		case RADIX_FLOAT:
			radixSortFloat((float *) array, size);
			break;
		case RADIX_DOUBLE:
			radixSortDouble((double *) array, size);
			break;
		case RADIX_LONG_LONG_INT:
			radixSortint64_t((int64_t *) array, size);
			break;
		case RADIX_UNSIGNED_CHAR: {
			uint32_t hist[256] = {0};
			uint8_t *temp      = malloc(size * sizeof(uint8_t));
			uint8_t *input     = (uint8_t *) array;
			
			for (i=0;i<size;i++)
				hist[input[i]]++;
			for (i=1;i<256;i++)
				hist[i] += hist[i-1];
			for (i=size-1;i>=0;i--)
				temp[--hist[input[i]]] = input[i];
				
			memcpy(input, temp, size * sizeof(uint8_t));
			free(temp);
		}
			break;
		case RADIX_UNSIGNED_SHORT:
			radixSortuint16_t((uint16_t *) array, size);
			break;
		case RADIX_UNSIGNED_INT:
		case RADIX_UNSIGNED_LONG:
			radixSortuint32_t((uint32_t *) array, size);
			break;
		case RADIX_UNSIGNED_LONG_LONG_INT:
			radixSortuint64_t((uint64_t *) array, size);
			break;
	}
}