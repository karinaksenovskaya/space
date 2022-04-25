#include "main_header.h"

int size = -1;

void swap (int *p1, int *p2){
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void* thread_func(void* arg){
    int *a = arg;
    int low;
    for (int i = 0 ; i < size - 1; i++){
        low = i;
        for (int j = i + 1; j < size; j++){
            if (*(a + j) < *(a + low)){
                low = j; 
            }
        }               
        if (low != i){
            swap(a + i, a + low);
        }
    }
    
    for(int i = 0; i < size; i++){
        printf("%d ", *a++);
    }
    printf("\n");
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    FILE *f;
    f = fopen(argv[1],"r");
    int l[100];
    for(int k = 0; !feof(f); k++){
        fscanf(f, "%d", &l[k]);
        size++;
    }
    fclose(f);

    printf("size - %d\n", size);
    //int buffer[MAX_READ] = {1, 55, 34, 67, 32, 48 ,14, 5, 11, 10}; 

    pthread_t thread;
    int result = pthread_create(&thread, NULL, thread_func, l);
    if(result != 0){
        perror("Creating the first thread");
        return EXIT_FAILURE;
    }

    result = pthread_join(thread, NULL);
    if(result != 0){
        perror("Joing the second thread");
        return EXIT_FAILURE;
    }

    return 0;
}