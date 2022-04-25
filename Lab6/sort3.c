#include "main_header.h"

int size = 10;

void swap(int* a,int* b) {int c=*a;*a=*b;*b=c;}

void* thread_func(void* arg){
    int* a = arg;
    for (int i = 0; i < size; i++) {
		for (int j = size - 1; j > 0; j--) {
			if (a[j] < a[j - 1]) {
				swap(&a[j], &a[j - 1]);
			}
		}
    }
    
    for(int i = 0; i < size; i++){
        printf("%d ", *a++);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){

    int buffer[] = {1, 55, 34, 67, 32, 48 ,14, 5, 11, 10}; 

    int result;

    pthread_t thread;

    pthread_attr_t attr;

    result = pthread_attr_init(&attr);

    if(result != 0){
        printf("Error pthread_attr_init()!");
        exit(EXIT_FAILURE); // Ошибка инициализации атрибута потока exit
    }

    result = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(result != 0){
        printf("Error pthread_attr_setdetachstate()!");
        exit(EXIT_FAILURE); // Ошибка установки атрибута разделения потоков exit
    }

    result = pthread_create(&thread, &attr, thread_func, buffer);
    if(result != 0){
        perror("Creating the first thread");
        return EXIT_FAILURE;
    }

    result = pthread_join(thread, NULL);
    if(result != 0){
        perror("Joing the second thread");
        return EXIT_FAILURE;
    }

    pthread_attr_destroy(&attr);

    sleep(5);

    return 0;
}