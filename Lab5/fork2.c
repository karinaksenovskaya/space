#include "perror_header.h"

static void atexitFunc1(){
    printf("atexit function 1 called\n");
}

int main(int argc, char* argv[]){
    pid_t childPid;
    switch (childPid = fork()) { 
        case (-1):
            perror("fork");
            exit(EXIT_FAILURE);
        case 0: 
            printf("This is child\n");
            if (atexit(atexitFunc1) != 0) { 
                perror("atexit 1"); 
            }
            break;
        default:
            printf("This is parent\n");
            break;
    }

}