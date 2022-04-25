#
# This is my first Makefile
#

pid: pid.o 
	gcc -o pid pid.c

pid.o: pid.c
	gcc -O0 -g3 -Wall -c pid.c

etext: etext.o 
	gcc -o etext etext.c

etext.o: etext.c
	gcc -O0 -g3 -Wall -c etext.c

envino: envino.o 
	gcc -o envino envino.c

envino.o: envino.c perror_header.h
	gcc -O0 -g3 -Wall -c envino.c

enva: enva.o 
	gcc -o enva enva.c

enva.o: enva.c perror_header.h
	gcc -O0 -g3 -Wall -c enva.c

clean:
	@echo "This is clean action"
	rm -rf pid etext envino enva *.o

all: pid etext envino enva