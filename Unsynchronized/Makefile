# the compiler: gcc for C program
CC = gcc
FLAGS = -lrt -g -c
OUT = unsynchronized 

# create an executable for the object file
output: unsynchronized.o 
	$(CC) unsynchronized.o -o output -lpthread

# create object file for Unsynchronized version
unsynchronized.o: Unsynchronized.c
	$(CC) $(FLAGS) Unsynchronized.c -o unsynchronized.o -lpthread 

clean:
	rm -f *.o $(OUT)




