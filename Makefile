#
# This is my first Makefile
#

kurs: kurs.o
	gcc -pthread -o kurs kurs.o

kurs.o: kurs.c header.h
	gcc -pthread -O0 -g3 -Wall -c kurs.c -DLINUX

kurs2: kurs2.o 
	gcc -pthread -o kurs2 kurs2.c

kurs2.o: kurs2.c
	gcc  -pthread -O0 -g3 -Wall -c kurs2.c

clean:
	@echo "This is clean action"
	rm -rf kurs kurs2 *.o

all: kurs kurs2