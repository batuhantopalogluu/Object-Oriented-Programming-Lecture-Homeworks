all: driver.o GTUNode.o GTUIterator.o GTUSet.o GTUMap.o
	g++ -std=c++11 driver.o GTUNode.o GTUMap.o GTUIterator.o GTUSet.o -o exe

driver.o: driver.cpp 
	g++ -std=c++11 -c driver.cpp 

GTUNode.o: GTUNode.cpp
	g++ -std=c++11 -c GTUNode.cpp

GTUIterator.o: GTUIterator.cpp
	g++ -std=c++11 -c GTUIterator.cpp

GTUSet.o: GTUSet.cpp
	g++ -std=c++11 -c GTUSet.cpp

GTUMap.o: GTUMap.cpp
	g++ -std=c++11 -c GTUMap.cpp

clean:
	rm *.o exe

