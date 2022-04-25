#
# This is my first Makefile
#

descriptor: descriptor.o
	gcc -o descriptor descriptor.c

descriptor.o: descriptor.c perror_header.h 
	gcc -O0 -g3 -Wall -c descriptor.c
	
tee: tee.o 
	gcc -o tee tee.c

tee.o: tee.c perror_header.h 
	gcc -O0 -g3 -Wall -c tee.c

cp: cp.o 
	gcc -o cp cp.c

cp.o: cp.c perror_header.h 
	gcc -O0 -g3 -Wall -c cp.c

rev: rev.o 
	gcc -o rev rev.c

rev.o: rev.c perror_header.h 
	gcc -O0 -g3 -Wall -c rev.c

clean:
	@echo "This is clean action"
	rm -rf descriptor tee cp rev *.o

all: descriptor tee cp rev