#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "RadixSort.hpp"
#include "Timing.hpp"

// #define DEBUG

#ifdef DEBUG
	#include <algorithm>
#endif

typedef int types;
int main (int argc, char *argv[]) {
    const int size = atoi(argv[1]);
    srand(time(NULL));
   
	std::vector<types> array(size);
	
	if (sizeof(types) == 1)
		for (int i=0;i<size;i++) {
			uint8_t *temp = (uint8_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0f);
			if (rand() % 2) *temp |= 0x80;
		}
	else if (sizeof(types) == 2)
		for (int i=0;i<size;i++) {
			uint16_t *temp = (uint16_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0fff);
			if (rand() % 2) *temp |= 0x8000;
		}
	else if (sizeof(types) == 4)
		for (int i=0;i<size;i++) {
			uint32_t *temp = (uint32_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0fffffff);
			if (rand() % 2) *temp |= 0x80000000;
		}
	else if (sizeof(types) == 8)
		for (int i=0;i<size;i++) {
			uint64_t *temp = (uint64_t *) &array[i];
			*temp = (((double) rand() / (RAND_MAX - 1)) * 0x0fffffffffffffff);
			if (rand() % 2) *temp |= 0x8000000000000000;
		}
		
#ifdef DEBUG
	std::vector<types> compare(array);
	std::sort(&compare[0], &compare[0] + size);
#endif
   
	scottgs::Timing timer;
	timer.start();
	RadixSort::sort(&array[0], size);
		RadixSort::sort(&array[0], size);
	timer.stop();

#ifndef DEBUG
    bool sorted = true;
    for (int i=1;i<size;i++)
        if (array[i] < array[i-1]) {
            sorted = false;
            break;
        }
    if (sorted) std::cout << "Array successfully sorted " << size << " elements in " << timer.getTotalElapsedTime() << " seconds.";
    else std::cout << "Error, unsuccessful at sorting array!";
	std::cout << std::endl;		
#else
	for (int i=0;i<size;i++)
		if (array[i] != compare[i])
			std::cout << i << ": " << array[i] << ' ' << compare[i] << std::endl;
#endif
    return 0;
}
