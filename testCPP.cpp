#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Timing.hpp"
//#include "RadixSort.hpp"

#if defined(FLOAT)
typedef float types;
#elif defined(INT)
typedef int types;
#elif defined(DOUBLE)
typedef double types;
#endif

#if defined(QSORT)
int compare (const void * a, const void * b) {
  return ( *(types*)a - *(types*)b );
}
#elif defined(MSORT)
void msort(types *array, int start, int stop) {
  if (stop <= start) return;
  int middle = (stop + start) >> 1;
  msort(array, start, middle);
  msort(array, middle+1, stop);
  std::inplace_merge(&array[start], &array[middle+1], &array[stop+1]);
}
#elif defined(RSORT)
#define _x1(x) (x & 0x7ff)
#define _x2(x) ((x >> 11) & 0x7ff)
#define _x3(x) ((x >> 22) & 0x7ff)
#define _x4(x) ((x >> 33) & 0x7ff)
#define _x5(x) ((x >> 44) & 0x7ff)
#define _x6(x) (x >> 55)
#ifdef DOUBLE
uint64_t forwardf64_t(uint64_t number) {
  if (number >> 63) return number ^ 0xffffffffffffffff;
  return number ^ 0x8000000000000000;
}
uint64_t backf64_t(uint64_t number) {
  if (number >> 63) return number ^ 0x8000000000000000;
  return number ^ 0xffffffffffffffff;
}
void rsort (double *start, int size) {
  uint32_t histA[2048] = {0}, histB[2048] = {0}, histC[2048] = {0};
  uint32_t histD[2048] = {0}, histE[2048] = {0}, histF[2048] = {0};
  uint64_t *temp = (uint64_t *) start;
  uint64_t *curr = new uint64_t[size];
  for (int i=0;i<size;i++) {
    temp[i] = forwardf64_t(temp[i]);
    histA[_x1(temp[i])]++;
    histB[_x2(temp[i])]++;
    histC[_x3(temp[i])]++;
    histD[_x4(temp[i])]++;
    histE[_x5(temp[i])]++;
    histF[_x6(temp[i])]++;
  }
  for (int i=1;i<2048;i++) {
    histA[i] += histA[i-1];
    histB[i] += histB[i-1];
    histC[i] += histC[i-1];
    histD[i] += histD[i-1];
    histE[i] += histE[i-1];
    histF[i] += histF[i-1];
  }
  for (int i=size-1;i>=0;i--)
    curr[--histA[_x1(temp[i])]] = temp[i];
  for (int i=size-1;i>=0;i--)
    temp[--histB[_x2(curr[i])]] = curr[i];
  for (int i=size-1;i>=0;i--)
    curr[--histC[_x3(temp[i])]] = temp[i];
  for (int i=size-1;i>=0;i--)
    temp[--histD[_x4(curr[i])]] = curr[i];
  for (int i=size-1;i>=0;i--)
    curr[--histE[_x5(temp[i])]] = temp[i];
  for (int i=size-1;i>=0;i--)
    temp[--histF[_x6(curr[i])]] = backf64_t(curr[i]);
  delete[] curr;
}

#else
uint32_t forwardf32_t(uint32_t number) {
  if (number >> 31) return number ^ 0xffffffff;
  return number ^ 0x80000000;
}
uint32_t backf32_t(uint32_t number) {
  if (number >> 31) return number ^ 0x80000000;
  return number ^ 0xffffffff;
}
uint32_t pos_int32_t(uint32_t number) {
  return number ^ 0x80000000;
}
void rsort (types *start, int size) {
  uint32_t histA[2048] = {0}, histB[2048] = {0}, histC[2048] = {0};
  uint32_t *temp = (uint32_t *) start;
  uint32_t *curr = new uint32_t[size];
  for (int i=0;i<size;i++) {
#ifdef FLOAT
    curr[i] = forwardf32_t(temp[i]);
#else
    curr[i] = pos_int32_t(temp[i]);
#endif
    histA[_x1(curr[i])]++;
    histB[_x2(curr[i])]++;
    histC[_x3(curr[i])]++;
  }
  for (int i=1;i<2048;i++) {
    histA[i] += histA[i-1];
    histB[i] += histB[i-1];
    histC[i] += histC[i-1];
  }
  for (int i=size-1;i>=0;i--)
    temp[--histA[_x1(curr[i])]] = curr[i];
  for (int i=size-1;i>=0;i--)
    curr[--histB[_x2(temp[i])]] = temp[i];
  for (int i=size-1;i>=0;i--)
#ifdef FLOAT
    temp[--histC[_x3(curr[i])]] = backf32_t(curr[i]);
#else
  temp[--histC[_x3(curr[i])]] = pos_int32_t(temp[i]);
#endif
  delete[] curr;
}

#endif
#endif
int main (int argc, char *argv[]) {
  const int size = atoi(argv[1]);
  srand(time(NULL));

  // bool *array = new bool[size];
  // for (int i=0;i<size;i++)
  // array[i] = rand() % 2;

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

  // #ifdef DEBUG
  // std::vector<types> compare(array);
  // std::sort(&compare[0], &compare[0] + size);
  // #endif

  scottgs::Timing timer;
  timer.start();
#if defined(RADIX)
  RadixSort::sort(&array[0], size);
#elif defined(NORM)
  std::sort(&array[0], &array[0] + size);
#elif defined(QSORT)
  qsort(&array[0], size, sizeof(types), compare);
#elif defined(MSORT)
  msort(&array[0], 0, size-1);
#elif defined(RSORT)
  rsort(&array[0], size);
#endif
  timer.stop();

  std::cout << size << ',' << timer.getTotalElapsedTime() << ',';
#if defined(NORM)
  std::cout << "std,";
#elif defined(RADIX)
  std::cout << "RadixSort,";
#elif defined(QSORT)
  std::cout << "qsort,";
#elif defined(MSORT)
  std::cout << "msort,";
#elif defined(RSORT)
  std::cout << "rsort,";
#endif

#if defined(FLOAT)
  std::cout << "FLOAT\n";
#elif defined(INT)
  std::cout << "INT\n";
#elif defined(DOUBLE)
  std::cout << "DOUBLE\n";
#endif

  return 0;
}
