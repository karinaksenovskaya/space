#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    printf("%d\n", getpid());
    printf("%d\n", getppid());
}