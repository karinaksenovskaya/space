#include "perror_header.h"

void pr_exit(int status){
    if (WIFEXITED(status)){
        printf("Нормальное завершение, код выхода = %d\n", WEXITSTATUS(status));
    }else if (WIFSIGNALED(status)){
        printf("Аварийное завершение, номер сигнала = %d\n", WTERMSIG(status));
    }else if (WIFSTOPPED(status)){
        printf("Дочерний процесс остановлен, номер сигнала = %d\n", WSTOPSIG(status));
    }
}

static void atexitFunc1(){
    printf("atexit function 1 called\n");
}

int main(int argc, char* argv[]){
    pid_t childPid;
    //extern char** environ;
    char *newargv[] = { argv[1], "hello", "world", NULL};
    //char *newenviron[] = { NULL };
    int status;
    switch (childPid = fork()) { 
        case (-1):
            perror("fork");
            exit(EXIT_FAILURE);
        case 0: 
            printf("This is child in fork7\n");
            if(execv(argv[1], newargv) == -1){
                perror("exec");
                exit(EXIT_FAILURE);
            }
            if (atexit(atexitFunc1) != 0) { 
                perror("atexit 1");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("Befor child\n");
            //sleep(5);
            if(waitpid(childPid,&status,0) != childPid){
                perror("wait");
                exit(1);
            }
            pr_exit(status);
            printf("This is parent in fork7\n");
            break;
    }
}