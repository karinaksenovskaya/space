#
# This is my first Makefile
#

main: main.o func.o 
	gcc -o main main.c func.c 

main.o: main.c main_header.h func.h
	gcc -O0 -g3 -Wall -c main.c

func.o: func.c func.h
	gcc -O0 -g3 -Wall -c func.c

clean:
	@echo "This is clean action"
	rm -rf main *.o

all: main