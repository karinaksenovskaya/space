#
# This is my first Makefile
#

ex: ex.o 
	gcc -pthread -o ex ex.c

ex.o: ex.c main_header.h
	gcc  -pthread -O0 -g3 -Wall -c ex.c

clean:
	@echo "This is clean action"
	rm -rf ex *.o

all: ex