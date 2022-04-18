all: mutex
mutex: mutex.o
	g++ -lsystemc -lpthread -o mutex mutex.o
main.o: mutex.cpp
	g++ -lsystemc -c mutex.cpp
clean:
	 rm -f mutex *.o
