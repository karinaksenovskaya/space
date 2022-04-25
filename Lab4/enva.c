#include "perror_header.h"
#include <linux/limits.h>

// int main(int argc, char* argv[]){

//     setenv("VAAR","this is var", 0);

    // extern char** environ;
    // char sep [10] = "=";
    // char *istr;
    // int num = 3;

    // char* tmp = NULL;
    // tmp = *environ;

    // while(num > 0){
    //     while(tmp != NULL){
    //         istr = strtok (tmp, sep);
    //         if(istr != NULL){
    //             printf("%s = ", istr);
    //         }
    //         istr = strtok (NULL, sep);
    //         if(istr != NULL){
    //             printf("%s\n", istr);
    //         }
    //         tmp++;
    //     }
    //     num--;
    //     tmp = *environ;
    // }
    // }

    extern char **environ;

    char prop[PATH_MAX] = { 0 };
    char *val = NULL;

    int remove_environ(int pos) {
        int i = 0;
        while(environ[++i] != NULL) {
            if(i == pos) {
                memset(prop, 0, PATH_MAX);
                val = strstr(environ[i],"=");
                strncpy(prop,environ[i], val - environ[i]);
                printf("UNSET %s\n",prop);
                return unsetenv(prop);
            }
        }
    }


    int main() {

        setenv("VAAR","this is var", 0);

        int user_choice = -1;
        int i = 0;

        do {
            while(environ[++i] != NULL) {
                memset(prop, 0, PATH_MAX);
                val = strstr(environ[i],"=");
                strncpy(prop,environ[i], val - environ[i]);
                val++;
                printf("%d [%s]=[%s]\n",i, prop, val);
            }
            printf("Enter env to be deleted: ");
            scanf("%d",&user_choice);
            if(user_choice < 0) {
                break;
            }
            remove_environ(user_choice);
            i = 0;
        } while(user_choice >= 0);
    }
