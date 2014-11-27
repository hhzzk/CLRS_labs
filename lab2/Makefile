OBJS = question2.o common.o
CC = gcc
CFLAGS = -Wall -O -g

question2 : $(OBJS)
	$(CC) $(OBJS) -o question2

common.o : common.c common.h
	$(CC) $(CFLAGS) -c common.c -o common.o

question2.o : question2.c common.h
	$(CC) $(CFLAGS) -c question2.c -o question2.o



clean:
	rm -rf *.o question2
