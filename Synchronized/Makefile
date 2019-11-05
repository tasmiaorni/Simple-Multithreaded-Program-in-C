# the compiler: gcc for C program
CC = gcc
FLAGS = -lrt -g -c
OUT = synchronized 

# create an executable for the object files
output: synchronized.o 
	$(CC) synchronized.o -o output -lpthread

# create object file for Synchronized version
synchronized.o: Synchronized.c
	$(CC) $(FLAGS) Synchronized.c -o synchronized.o -lpthread 

clean:
	rm -f *.o $(OUT)




