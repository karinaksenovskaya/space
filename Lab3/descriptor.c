#include "perror_header.h"
#define MAX_READ 2000

int main(int argc, char* argv[]){

    int fd = open("cp.c", O_RDONLY);
    printf("%d\n",fd);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    
    if(close(fd) == -1){
        perror("close");
        exit(EXIT_FAILURE);
    }

    fd = open("cp.c", O_RDONLY);
    printf("%d\n",fd);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    //close(fd);

    return 0;
}


