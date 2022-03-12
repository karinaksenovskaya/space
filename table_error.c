#include "perror_header.h"

int main(int argc, char *argv[]){
    for(int i=0; i<134; i++){
        printf("Error %d: %s\n", i, strerror(i)); // не понимаю как вывести название ошибок
    }
}