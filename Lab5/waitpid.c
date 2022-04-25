#include "perror_header.h"

/*
WIFEXITED - возвращает истинное значение, если потомок нормально завершился
WIFESIGNALED - возвращает истинное значение, если потомок завершился из-за сигнала
WIFSTOPPED - возвращает истинное значение, если потомок остановлен по сигналу 
WIFCONTINUED - возвращает истинное значение, если потомок продолжил работу, получив сигнал SIGCONT
*/

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
    int status;
    switch (childPid = fork()) { 
        case (-1):
            perror("fork");
            exit(EXIT_FAILURE);
        case 0: 
            printf("This is child\n");
            if (atexit(atexitFunc1) != 0) { 
                perror("atexit 1"); 
                exit(1);
            }
            break;
        default:
            if(waitpid(childPid,&status,0) != childPid){
                perror("wait");
                exit(1);
            }
            pr_exit(status);
            printf("This is parent\n");
            break;
    }
}