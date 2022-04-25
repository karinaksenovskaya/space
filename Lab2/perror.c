#include "perror_header.h"
#define value (5)

int main(int argc, char** argv){
    int errnum = open("mainn", O_RDONLY); 
    printf("%d\n", value);
    if (errnum == -1) { 
        perror(argv[0]); 
        exit(EXIT_FAILURE); 
    } 
}