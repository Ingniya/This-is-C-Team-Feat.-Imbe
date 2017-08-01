CC = gcc
CFLAGS = -lpthread -g -I./
SRCSERVER = .
BINSERVER = .

all: program

program: thread_testex.o
	${CC} ${CFLAGS} $^ -o ${BINSERVER}/thread_test.out


clean:
	rm -f *.o
	rm -f ${BINSERVER}/*.out
