#include "perror_header.h"
#define MAX_READ 2000
#define LINE_LENGHT 10

int main(int argc, char* argv[]){
    ssize_t numRead;

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_READ] = {"\0"};
    
    numRead = read(fd, buffer, MAX_READ);
    if(numRead == -1){
        perror("read");
        exit(EXIT_FAILURE);
    }

    buffer[numRead] = '\n';

    if(close(fd) == -1){
        perror("\nclose fd");
        exit(EXIT_FAILURE);
    }
    fd = -1;
    
    //write(STDOUT_FILENO, buffer, MAX_READ);

    char buf[MAX_READ] = {"\0"};

    int count[LINE_LENGHT];
    int counter = 0;
    int i = 0;
    int j = 0;
    while(buffer[i] != '\0'){
        while(buffer[i] != '\n'){
            counter++;
            i++;
        }
        counter++;
        count[j] = counter;
        j++;
        i++;
    }

    int l = 0;
    int m = count[l]-1;
    int k = 0;
    while(buffer[k] != '\0'){
        for(int i = k-1; i < count[l]; ++i, --m){
            buf[m] = buffer[i];  
        }
        k = count[l];
        l++;
        m = count[l];
    }

    write(STDOUT_FILENO, buf, MAX_READ);

    return 0;
}