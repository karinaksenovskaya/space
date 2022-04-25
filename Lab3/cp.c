#include "perror_header.h"
#define MAX_READ 2000
int main(int argc, char* argv[]){
    int fd = open(argv[1],O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    ssize_t numRead;
    char buffer[MAX_READ]={"\0"};
    numRead = read(fd, buffer, MAX_READ);
    if(numRead == -1){
        perror("read");
        exit(EXIT_FAILURE);
    }
    int xd = open(argv[2], O_CREAT | O_WRONLY);
    if(xd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(xd, buffer, MAX_READ);
    if(fd >= 0){
        if(close(fd) == -1){
            perror("close");
            exit(EXIT_FAILURE);
        }
        fd = -1;
    }
    if(xd >= 0){
        if(close(xd) == -1){
            perror("close");
            exit(EXIT_FAILURE);
        }
        xd = -1;
    }

    return 0;
}