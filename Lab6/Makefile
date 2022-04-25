#
# This is my first Makefile
#

sort: sort.o 
	gcc -pthread -o sort sort.c

sort.o: sort.c main_header.h
	gcc  -pthread -O0 -g3 -Wall -c sort.c

sort2: sort2.o 
	gcc -pthread -o sort2 sort2.c

sort2.o: sort2.c main_header.h
	gcc  -pthread -O0 -g3 -Wall -c sort2.c

sort3: sort3.o 
	gcc -pthread -o sort3 sort3.c

sort3.o: sort3.c main_header.h
	gcc  -pthread -O0 -g3 -Wall -c sort3.c

clean:
	@echo "This is clean action"
	rm -rf sort sort2 sort3 *.o

all: sort sort2 sort3