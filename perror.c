#include "perror_header.h"

int main(int argc, char** argv){
    int errnum = open("main", O_RDONLY); 
    printf("%d\n", errnum);
    if (errnum == -1) { 
        perror("Error"); 
        exit(EXIT_FAILURE); 
    } 
}