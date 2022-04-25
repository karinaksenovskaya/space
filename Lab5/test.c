#include <stdio.h>

int main(int argc, char* argv[]){
    printf("This is test\n");
    for(int j = 0; j < argc; j++){
        printf("[%d] - %s\n", j, argv[j]);
    }
    return 0;
}