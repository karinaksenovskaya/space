#include "header.h"
#define MAX_ARRAY 5

#ifdef LINUX
//Объявление глобального индентификатора мьютекса
pthread_mutex_t mtx;
#endif //LINUX

#ifdef WINDOWS
//Объявление глобального индентификатора критической области
PCRITICAL_SECTION critsect;
#endif //WINDOWS

int array[MAX_ARRAY] = {-1};

void* producer(void* p){
    printf("PRODUCER RESOURCE ROUTINE\n");

    #ifdef LINUX
    //Получаем исключительный доступ к массиву
    (void)pthread_mutex_lock(&mtx);
    #endif //LINUX

    #ifdef WINDOWS
    //Входим в критическиую секцию, которая блокирует доступ другим потокам к массиву
	EnterCriticalSection(&critsect);
    #endif //WINDOWS

    if(*array == -1){
        for (int i = 0; i < MAX_ARRAY; i++) {
		    array[i] = i;
	    }
    }else{
        printf("ERROR: array is voll in producer\n");    
    }
    sleep(2);

    #ifdef LINUX
    //Высвобождаем мьютекс
    (void)pthread_mutex_unlock(&mtx);
    #endif //LINUX

    #ifdef WINDOWS
	//Выходим из критической области данного потока и перенаправляем ресурсы в другой ожидающий поток
	LeaveCriticalSection(&critsect);
    #endif //WINDOWS

    #ifdef LINUX
    //Завершение потока
    pthread_exit((void*)0);
    #endif //LINUX

    #ifdef WINDOWS
	//Завершение потока
	_endthread();
    #endif //WINDOWS
}

void* print(){
    printf("PRINT RESOURCE ROUTINE\n");

    #ifdef LINUX
    //Получаем исключительный доступ к массиву
    (void)pthread_mutex_lock(&mtx);
    #endif //LINUX

    #ifdef WINDOWS
	//Входим в критическиую секцию, которая блокирует доступ другим потокам к массиву
	EnterCriticalSection(&critsect);
    #endif //WINDOWS

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

    #ifdef LINUX
    //Высвобождаем мьютекс
    (void)pthread_mutex_unlock(&mtx);
    //Завершение потока
    pthread_exit((void*)0);
    #endif //LINUX

    #ifdef WINDOWS
	//Выходим из критической области данного потока и перенаправляем ресурсы в другой ожидающий поток
	LeaveCriticalSection(&critsect);
    //Завершение потока
	_endthread();
    #endif //WINDOWS
}

void* consumer(void *p){
    printf("CONSUMER RESOURCE ROUTINE\n");

    #ifdef LINUX
    //Получаем исключительный доступ к массиву
    (void)pthread_mutex_lock(&mtx);
    #endif //LINUX

    #ifdef WINDOWS
	//Входим в критическиую секцию, которая блокирует доступ другим потокам к массиву
	EnterCriticalSection(&critsect);
    #endif //WINDOWS

    if(*array == -1){
        for (int i = 0; i < MAX_ARRAY; i++) {
		    array[i] = i+5;
	    }
    }else{
        printf("ERROR: array is voll in consumer\n");
    }
    sleep(2);

    #ifdef LINUX
    //Высвобождаем мьютекс
    (void)pthread_mutex_unlock(&mtx);
    //Завершение потока
    pthread_exit((void*)0);
    #endif //LINUX

    #ifdef WINDOWS
	//Выходим из критической области данного потока и перенаправляем ресурсы в другой ожидающий поток
	LeaveCriticalSection(&critsect);
    //Завершение потока
	_endthread();
    #endif //WINDOWS
}

int main(int argc, char* argv[]){

    #ifdef LINUX
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
    #endif //LINUX

    #ifdef WINDOWS

	DWORD status;

	//Инициализция критической области
	InitializeCriticalSection(&critsect);

	//Создание потока producer 
	HANDLE h_process_command_thread_producer = (HANDLE)_beginthread(ProducerArray, 0, NULL);
	if (h_process_command_thread_producer == -1) {
		printf("Error begin thread producer\n");
		return 1;
	}

	//Создание потока print
	HANDLE h_process_command_thread_print_1 = (HANDLE)_beginthread(PrintArray, 0, NULL);
	if (h_process_command_thread_print_1 == -1) {
		printf("Error begin thread print 1\n");
		return 1;
	}

	//Создание потока consumer
	HANDLE h_process_command_thread_consumer = (HANDLE)_beginthread(ConsumerArray, 0, NULL);
	if (h_process_command_thread_consumer == -1) {
		printf("Error begin thread consumer\n");
		return 1;
	}

	//Повторное создание потока print
	HANDLE h_process_command_thread_print_2 = (HANDLE)_beginthread(PrintArray, 0, NULL);
	if (h_process_command_thread_print_2 == -1) {
		printf("Error begin thread print 2\n");
		return 1;
	}

	//Ожидание завершения потока producer
	status = WaitForSingleObject(h_process_command_thread_producer, -1);
	switch (status) {
		case  WAIT_OBJECT_0:
			// Поток завершен
			printf("Thread Producer has ended\n");
			break;
		case  WAIT_TIMEOUT:
			// Поток не завершился в течение времени ожидания
			printf("The thread Producer did not complete within the timeout\n");
			break;
		case  WAIT_FAILED:
			// Неверный вызов функции
			printf("Thread Producer ERROR\n");
			return 1;
	}

	//Ожидание завершения потока print 1
	status = WaitForSingleObject(h_process_command_thread_print_1, -1);
	switch (status) {
	case  WAIT_OBJECT_0:
		// Поток завершен
		printf("Thread Print 1 has ended\n");
		break;
	case  WAIT_TIMEOUT:
		// Поток не завершился в течение времени ожидания
		printf("The thread Print 1 did not complete within the timeout\n");
		break;
	case  WAIT_FAILED:
		// Неверный вызов функции
		printf("Thread Print 1 ERROR\n");
		return 1;
	}

	//Ожидание завершения потока consumer
	status = WaitForSingleObject(h_process_command_thread_consumer, -1);
	switch (status) {
	case  WAIT_OBJECT_0:
		// Поток завершен
		printf("Thread Consumer has ended\n");
		break;
	case  WAIT_TIMEOUT:
		// Поток не завершился в течение времени ожидания
		printf("The thread Consumer did not complete within the timeout\n");
		break;
	case  WAIT_FAILED:
		// Неверный вызов функции
		printf("Thread Consumer ERROR\n");
		return 1;
	}

	//Ожидание завершения потока print 2
	status = WaitForSingleObject(h_process_command_thread_print_2, -1);
	switch (status) {
	case  WAIT_OBJECT_0:
		// Поток завершен
		printf("Thread Print 2 has ended\n");
		break;
	case  WAIT_TIMEOUT:
		// Поток не завершился в течение времени ожидания
		printf("The thread Print 2 did not complete within the timeout\n");
		break;
	case  WAIT_FAILED:
		// Неверный вызов функции
		printf("Thread Print 2 ERROR\n");
		return 1;
	}

	//Удаляем критическую секцию
	DeleteCriticalSection(&critsect);
    #endif //WINDOWS

    return 0;
}