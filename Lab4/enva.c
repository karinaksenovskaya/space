#include "perror_header.h"

int main(int argc, char* argv[]){

    setenv("VAAR","this is var", 0);

    extern char** environ;
    char sep [10] = "=";
    char *istr;
    int num = 3;

    char* tmp = NULL;
    tmp = *environ;

    while(num > 0){
        while(tmp != NULL){
            istr = strtok (tmp, sep);
            if(istr != NULL){
                printf("%s = ", istr);
            }
            istr = strtok (NULL, sep);
            if(istr != NULL){
                printf("%s\n", istr);
            }
            tmp++;
        }
        num--;
        tmp = *environ;
    }
}