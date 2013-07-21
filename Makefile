# flags to pass compiler
OTHER_FLAGS =-std=c++0x -g
#-O2 -ffast-math -g
C_FLAGS = -g -fPIC
THREAD_FLAGS =-pthread -fopenmp

# Standard all target
all: RadixSortLibC RadixSortLibCPP RadixTestC RadixTestCPP
# all: myProc

RadixTestCPP: testCPP.o Timing.o
	g++ -o SortCPP testCPP.o Timing.o -L. -lRadixSortCPP $(THREAD_FLAGS)
	
RadixTestC: testC.o
	gcc -o SortC testC.o -L. -lRadixSortC $(THREAD_FLAGS)

testCPP.o: testCPP.cpp
	g++ $(OTHER_FLAGS) -Wall -c testCPP.cpp
	
testC.o: testC.c
	gcc $(C_FLAGS) -Wall -c testC.c
	
RadixSortLibCPP: Histogram_64.o Histogram_32.o Histogram_16.o RadixSortTypes.o RadixSortCPP.o
	g++ -shared -o libRadixSortCPP.so RadixSortCPP.o Histogram_16.o Histogram_32.o Histogram_64.o RadixSortTypes.o
	
RadixSortLibC: Histogram_64.o Histogram_32.o Histogram_16.o RadixSortTypes.o RadixSortC.o
	gcc -shared -o libRadixSortC.so RadixSortC.o Histogram_16.o Histogram_32.o Histogram_64.o RadixSortTypes.o
	
RadixSortCPP.o: RadixSort.cpp RadixSort.hpp
	g++ $(OTHER_FLAGS) -Wall -c -o RadixSortCPP.o -fPIC RadixSort.cpp $(THREAD_FLAGS)
	
RadixSortC.o: RadixSort.c RadixSort.h
	gcc $(C_FLAGS) -Wall -c -o RadixSortC.o -fPIC RadixSort.c $(THREAD_FLAGS)
	
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
