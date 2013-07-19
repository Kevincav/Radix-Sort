# flags to pass compiler
OTHER_FLAGS =-std=c++0x
#-O2 -ffast-math -g
C_FLAGS =
THREAD_FLAGS =-lpthread -fopenmp

# Standard all target
all: RadixSortLib  myProc
# all: myProc

myProc: test.o Timing.o RadixSort.a
	g++ -o Sort test.o Timing.o RadixSort.a $(THREAD_FLAGS)

test.o: test.cpp
	g++ $(OTHER_FLAGS) -Wall -c test.cpp
	
RadixSortLib:  Histogram_64.o Histogram_32.o RadixSort.o RadixSortTypes.o
	ar -rs RadixSort.a RadixSort.o Histogram_32.o Histogram_64.o RadixSortTypes.o
	
RadixSort.o: RadixSort.cpp RadixSort.hpp
	g++ $(OTHER_FLAGS) -Wall -c RadixSort.cpp $(THREAD_FLAGS)
	
Histogram_32.o: Histogram_32.c Histogram_32.h
	gcc $(C_FLAGS) -Wall -c Histogram_32.c $(THREAD_FLAGS)
	
Histogram_64.o: Histogram_64.c Histogram_64.h
	gcc $(C_FLAGS) -Wall -c Histogram_64.c $(THREAD_FLAGS)
	
RadixSortTypes.o: RadixSortTypes.c RadixSortTypes.h
	gcc $(C_FLAGS) -Wall -c RadixSortTypes.c $(THREAD_FLAGS)
	
Timing.o: Timing.cpp Timing.hpp
	g++ $(OTHER_FLAGS) -Wall -c Timing.cpp

clean:
	rm -f *.o *.a Sort
