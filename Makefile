#
# This is my first Makefile
#

main: main.o func.o 
	gcc -o main main.o func.o 

main.o: main.c
	gcc -O0 -g3 -Wall -c main.c

func.o: func.c 
	gcc -O0 -g3 -Wall -c func.c 

clean:
	@echo "This is clean action"
	rm -rf main *.o

all: main