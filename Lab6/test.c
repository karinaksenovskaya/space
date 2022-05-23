#include "main_header.h"

void* func(){
    printf("Hello\n");
}

int main(){
    pthread_t thread;

    int result = pthread_create(&thread,NULL,func,NULL);
    usleep(1);
}