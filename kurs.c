#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_ARRAY 5

//Объявление глобального индентификатора мьютекса
pthread_mutex_t mtx;

int array[MAX_ARRAY] = {-1};

void* producer(void* p){
    printf("PRODUCER RESOURCE ROUTINE\n");
    //Получаем исключительный доступ к массиву
    (void)pthread_mutex_lock(&mtx);
    if(*array == -1){
        for (int i = 0; i < MAX_ARRAY; i++) {
		    array[i] = i;
	    }
    }else{
        printf("ERROR: array is voll in producer\n");    
    }
    sleep(2);
    //Высвобождаем мьютекс
    (void)pthread_mutex_unlock(&mtx);

    //Завершение потока
    pthread_exit((void*)0);
}

void* print(){
    printf("PRINT RESOURCE ROUTINE\n");
    //Получаем исключительный доступ к массиву
    (void)pthread_mutex_lock(&mtx);
    if(*array != -1){
        for(int i = 0; i < MAX_ARRAY; i++){
            printf("%d ", array[i]);
        }
        printf("\n");
        memset(array, -1, sizeof(array));
    }else{
        printf("ERROR: array is empty\n");
    }
    sleep(2);
    //Высвобождаем мьютекс
    (void)pthread_mutex_unlock(&mtx);

    //Завершение потока
    pthread_exit((void*)0);
}

void* consumer(void *p){
    printf("CONSUMER RESOURCE ROUTINE\n");
    //Получаем исключительный доступ к массиву
    (void)pthread_mutex_lock(&mtx);
    if(*array == -1){
        for (int i = 0; i < MAX_ARRAY; i++) {
		    array[i] = i+5;
	    }
    }else{
        printf("ERROR: array is voll in consumer\n");
    }
    sleep(2);
    //Высвобождаем мьютекс
    (void)pthread_mutex_unlock(&mtx);

    //Завершение потока
    pthread_exit((void*)0);
}

int main(int argc, char* argv[]){

    int status;

    //Объявление индентификаторов создаваемых потоков
    pthread_t thread_producer, thread_consumer, thread_print; 

    //Инициализация мьютекса
    if(pthread_mutex_init(&mtx, NULL) != 0){
        perror("CREATE MUTEX ERROR");
        return 1;
    }

    //Создание потока с индентификатором thread_producer и передача в нее функции producer
    if(pthread_create(&thread_producer, NULL, producer, NULL) != 0){
        perror("CREATE PRODUCER ERROR");
        return 1;
    }

    //Создание потока с индентификатором thread_print и передача в нее функции print
    if(pthread_create(&thread_print, NULL, print, NULL) != 0){
        perror("CREATE PRINT ERROR");
        return 1;
    }

    //Создание потока с индентификатором thread_consumer и передача в нее функции consumer
    if(pthread_create(&thread_consumer, NULL, consumer, NULL) != 0){
        perror("CREATE CONSUMER ERROR");
        return 1;
    }

    //Повторное создание потока с индентификатором thread_print и передача в нее функции print
    if(pthread_create(&thread_print, NULL, print, NULL) != 0){
        perror("CREATE PRINT ERROR");
        return 1;
    }

    //Ожидаем завершение потока с индентификатором thread_producer
    status = pthread_join(thread_producer, NULL) ;
    
    switch(status){
        case 0:
            printf("PRODUCER PTHREAD HAS ENDED\n");
            break;
        default:
            perror("JOIN PRODUCER ERROR\n");
            return 1;
    }

    //Ожидаем завершение потока с индентификатором thread_consumer
    status = pthread_join(thread_consumer, NULL);

    switch(status){
        case 0:
            printf("CONSUMER PTHREAD HAS ENDED\n");
            break;
        default:
            perror("JOIN CONSUMER ERROR\n");
            return 1;
    }

    //Ожидаем завершение потока с индентификатором thread_print
    status = pthread_join(thread_print, NULL);

    switch(status){
        case 0:
            printf("PRINT PTHREAD HAS ENDED\n");
            break;
        default:
            perror("JOIN PRINT ERROR\n");
            return 1;
    }

    //Уничтожаем созданный мьютекс и освобождаем ресурсы
    if(pthread_mutex_destroy(&mtx) != 0){
        perror("DESTROY MUTEX ERROR");
        return 1; 
    }

    return 0;
}