CC = gcc
CFLAGS = -lpthread -g -I./
SRCSERVER = .
BINSERVER = .

all: server

server: thread_mutex_testex.o DoubleLinkedList.o
	${CC} ${CFLAGS} $^ -o ${BINSERVER}/mutex_test.out

all: modify

modify: thread_mutex_testex2.o DoubleLinkedList.o
	${CC} ${CFLAGS} $^ -o ${BINSERVER}/mutex_test2.out

clean:
	rm -f *.o
	rm -f ${BINSERVER}/*.out
