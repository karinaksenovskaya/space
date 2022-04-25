#include <gnu/libc-version.h> 
#include <stdio.h>

int main(int argc, char *argv[]){
    printf("%s\n", gnu_get_libc_version());
}