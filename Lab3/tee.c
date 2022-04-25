#include "perror_header.h"
#define MAX_READ 20
int main(int argc, char* argv[]){
    ssize_t numRead;
    char buffer[MAX_READ]={'\0'};
    while(1){
        //char buffer[MAX_READ]={'\0'};
        numRead = read(STDIN_FILENO, buffer, MAX_READ);
        if(numRead == -1){
            perror("read");
            exit(EXIT_FAILURE);
        }
        write(STDOUT_FILENO, buffer, MAX_READ);
        for(int i = 0; i < MAX_READ; i++){
            buffer[i] = '\0';
        }
    }
    return 0;
}