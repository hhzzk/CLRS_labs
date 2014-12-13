OBJ1 = question1.o common.o
OBJ2 = question2.o common.o
CC = gcc
CFLAGS = -Wall -O -g

all: question1 question2 clean_o
question1 : $(OBJ1)
	$(CC) $(OBJ1) -o question1
question2 : $(OBJ2)
	$(CC) $(OBJ2) -o question2

common.o : common.c common.h
	$(CC) $(CFLAGS) -c common.c -o common.o

question1.o: question1.c common.h
	$(CC) $(CFLAGS) -c question1.c -o question1.o

question2.o : question2.c common.h
	$(CC) $(CFLAGS) -c question2.c -o question2.o

clean_o:
	rm -rf *.o

clean:
	rm -rf question2 question1
