#include "main_header.h"
#include "func.h"

int main(int argc, char *argv[]){
    int a = 1;
    int b = 2;
    int c[20];
    for(int i = 0; i<20; i++){
        c[i]=i;
    }
    printf("This is main\n");
	(void)func();
    return 0;
}