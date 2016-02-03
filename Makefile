CXX = g++

CXXFLAGS = -g -Wall -std=c++11

BINARIES = prog1

tests: ${BINARIES}
	   ./prog1

prog1: Main.o Hashtable.o Student.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o *.txt
