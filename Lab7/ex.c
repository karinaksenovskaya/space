#include "main_header.h"

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102
#define count 5
#define counter 7

typedef struct Node {
    int a;
    int b;
    struct Node* next;
}Node;

Node *head = NULL;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void push(int value){
    Node *tmp = malloc(sizeof(Node));
    if(head == NULL){
        tmp->next = NULL;
        tmp->a = value;
        head = tmp;
    }else{
        tmp->next = head;
        tmp->a = value;
        head = tmp;
    }
}

int pop(){
    Node* out = malloc(sizeof(sizeof(Node)));
    if(head == NULL){
        printf("Error\n");
        exit(STACK_UNDERFLOW);
    }else{
        out = head;
        head = head->next;
        return out->a;
    }
}

void* producer(void* p){
    printf("PRODUCER RESOURCE ROUTINE\n");
    //int count = 0;
    //while(count < counter){
        (void)pthread_mutex_lock(&mtx);
        int rand1 = rand()%100;
        //printf("rand1 = %d\n", rand1);
        int rand2 = rand()%100;
        //printf("rand2 = %d\n", rand2);
        push(rand1);
        push(rand2);  
        (void)pthread_mutex_unlock(&mtx);
        //count++;
    //}
    
    pthread_exit((void*)0);
}

void* consumer(void *p){
    printf("CONSUMER RESOURCE ROUTINE\n");
    //int count = 0;
    //while(count < counter2){
        (void)pthread_mutex_lock(&mtx);
        int a = pop();
        int b = pop();  
        printf("SUM = %d\n", a+b);
        (void)pthread_mutex_unlock(&mtx);
        //count++;
    //}
    pthread_exit((void*)0);

}

int main(int argc, char* argv[]){

    srand(time(NULL));

    pthread_t thread_producer, thread_consumer; 

    int result;

    for (size_t i = 0; i < count; i++){
        result = pthread_create(&thread_producer, NULL, producer, NULL);

        if (result != 0){
            perror("CREATE PRODUCER ERROR");
            return 1;
        }
    }
    
    for (size_t i = 0; i < counter; i++){
        result = pthread_create(&thread_consumer, NULL, consumer, NULL);

        if (result != 0){
            perror("CREATE CONSUMER ERROR");
            return 1;
        }
    }

    if(pthread_join(thread_producer, NULL) != 0){
        perror("Error join_thread_consumer\n");
        exit (EXIT_FAILURE);
    }

    if(pthread_join(thread_consumer, NULL) != 0){
        perror("Error join_thread_consumer\n");
        exit (EXIT_FAILURE);
    }

    free(head);

    return 0;
}