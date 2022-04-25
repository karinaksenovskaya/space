#include "perror_header.h"

int main(int argc, char* argv[]){
    if(argv[2] == 0){
        printf("%s\n", getenv(argv[1]));
    }else{
        setenv(argv[1], argv[3], 0);
        extern char** environ; 
        while (*environ != NULL) { 
            printf("%s\n", *environ); 
            environ++; 
        }
    }

    return 0;
}