#include "perror_header.h"
#define ERROR_NUM (134)
int main(int argc, char *argv[]){
    for(int i=0; i<ERROR_NUM; i++){
        printf("Error %d: %s\n", i, strerror(i)); //не понимаю как вывести название ошибок
    }
}