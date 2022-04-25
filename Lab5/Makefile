#
# This is my first Makefile
#

fork: fork.o 
	gcc -o fork fork.c

fork.o: fork.c perror_header.h
	gcc -O0 -g3 -Wall -c fork.c

fork2: fork2.o 
	gcc -o fork2 fork2.c

fork2.o: fork2.c perror_header.h
	gcc -O0 -g3 -Wall -c fork2.c

waitpid: waitpid.o 
	gcc -o waitpid waitpid.c

waitpid.o: waitpid.c perror_header.h
	gcc -O0 -g3 -Wall -c waitpid.c

zomby: zomby.o 
	gcc -o zomby zomby.c

zomby.o: zomby.c perror_header.h
	gcc -O0 -g3 -Wall -c zomby.c

fork7: fork7.o 
	gcc -o fork7 fork7.c

fork7.o: fork7.c perror_header.h
	gcc -O0 -g3 -Wall -c fork7.c

test: test.o 
	gcc -o test test.c

test.o: test.c
	gcc -O0 -g3 -Wall -c test.c

clean:
	@echo "This is clean action"
	rm -rf fork fork2 waitpid zomby fork7 test *.o

all: fork fork2 waitpid zomby fork7 test