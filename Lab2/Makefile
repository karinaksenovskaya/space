#
# This is my first Makefile
#

glibc-version: glibc-version.o
	gcc -o glibc-version glibc-version.c

glibc-version.o: glibc-version.c
	gcc -O0 -g3 -Wall -c glibc-version.c

perror: perror.o 
	gcc -o perror perror.c

perror.o: perror.c perror_header.h
	gcc -O0 -g3 -Wall -c perror.c

table_error: table_error.o 
	gcc -o table_error table_error.c

table_error.o: table_error.c perror_header.h
	gcc -O0 -g3 -Wall -c table_error.c 

clean:
	@echo "This is clean action"
	rm -rf glibc-version perror table_error *.o

all: glibc-version perror table_error