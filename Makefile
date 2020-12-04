###########################################################################
##                    Makefile for HW2 (LinkedList)                      ##
###########################################################################

CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3
EXECS    = cheshire

LinkedList: testLinkedList.o LinkedList.o
	${CXX} ${LDFLAGS} ${CXXFLAGS} -o ${EXECS} testLinkedList.o \
						LinkedList.o

testLinkedList.o: testLinkedList.cpp
LinkedList.o:     LinkedList.cpp LinkedList.h

clean:
	rm ${EXECS} *.o *.dSYM

provide:
	provide comp15 hw2 LinkedList.h LinkedList.cpp \
                           testLinkedList.cpp Makefile

## If you would like to submit other files, you may do so.
## Just add them to the provide command.  To add additional
## lines, you must add a \ to end of the previous line with
## NOTHING after it except the newline character.
