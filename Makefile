# flags to pass compiler
OTHER_FLAGS =-std=c++0x -g
#-O2 -ffast-math -g
C_FLAGS = -g -fPIC
THREAD_FLAGS =-lpthread -fopenmp

# Standard all target
all: RadixSortLib  myProc
# all: myProc

myProc: test.o Timing.o
	g++ -o Sort test.o Timing.o -L. -lRadixSort $(THREAD_FLAGS)

test.o: test.cpp
	g++ $(OTHER_FLAGS) -Wall -c test.cpp
	
RadixSortLib:  Histogram_64.o Histogram_32.o Histogram_16.o RadixSort.o RadixSortTypes.o
	g++ -shared -o libRadixSort.so RadixSort.o Histogram_16.o Histogram_32.o Histogram_64.o RadixSortTypes.o
	
RadixSort.o: RadixSort.cpp RadixSort.hpp
	g++ $(OTHER_FLAGS) -Wall -c -fPIC RadixSort.cpp $(THREAD_FLAGS)
	
Histogram_16.o: Histogram_16.c Histogram_16.h
	gcc $(C_FLAGS) -Wall -c Histogram_16.c $(THREAD_FLAGS)
		
Histogram_32.o: Histogram_32.c Histogram_32.h
	gcc $(C_FLAGS) -Wall -c Histogram_32.c $(THREAD_FLAGS)
	
Histogram_64.o: Histogram_64.c Histogram_64.h
	gcc $(C_FLAGS) -Wall -c Histogram_64.c $(THREAD_FLAGS)
	
RadixSortTypes.o: RadixSortTypes.c RadixSortTypes.h
	gcc $(C_FLAGS) -Wall -c RadixSortTypes.c $(THREAD_FLAGS)
	
Timing.o: Timing.cpp Timing.hpp
	g++ $(OTHER_FLAGS) -Wall -c Timing.cpp

clean:
	rm -f *.o *.a *.so Sort
