#
# This is my first Makefile
#

sig: sig.o 
	gcc -pthread -o sig sig.c

sig.o: sig.c main_header.h
	gcc  -pthread -O0 -g3 -Wall -c sig.c

clean:
	@echo "This is clean action"
	rm -rf sig *.o

all: sig