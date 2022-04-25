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
    //char cmd[4096];
    int status;
    pid_t childPid;
    printf("Parent PID = %ld\n", (long)getpid());
    switch (childPid = fork()){
        case (-1):
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            printf("Child PID = %ld\n", (long)getpid());
            if (atexit(atexitFunc1) != 0) { 
                perror("atexit 1"); 
                exit(1);
            }
            break;
        default:
            sleep(5);
            kill(childPid, SIGKILL);
            sleep(5);
            if(waitpid(childPid,&status,0) != childPid){
                perror("wait");
                exit(1);
            }
            pr_exit(status);


    }
}