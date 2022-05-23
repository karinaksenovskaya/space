#include "main_header.h"

void pr_exit(int status){
    if (WIFEXITED(status)){
        printf("Нормальное завершение, код выхода = %d\n", WEXITSTATUS(status));
    }else if (WIFSIGNALED(status)){
        printf("Аварийное завершение, номер сигнала = %d\n", WTERMSIG(status));
    }else if (WIFSTOPPED(status)){
        printf("Дочерний процесс остановлен, номер сигнала = %d\n", WSTOPSIG(status));
    }
}

void sigusr1(){
    printf("This is SIGUSR1\n");
}

void sigusr2(){
    printf("This is SIGUSR2\n");
}

void atexitFunc1(){
    pid_t parentPid = getppid();
    int parity = 0;
    while(1){
        sleep(5);
        if(parity % 2 == 0){
            parity++;
            kill(parentPid, SIGUSR1);
        }else{
            parity--;
            kill(parentPid, SIGUSR2);
        }
    }

}

int main(int argc, char* argv[]){
    pid_t childPid = fork();
    int status;
    switch (childPid) { 
        case (-1):
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            if (atexit(atexitFunc1) != 0) { 
                perror("atexit 1"); 
            }
            break;
        default:
            (void)signal(SIGUSR1, sigusr1);
            (void)signal(SIGUSR2, sigusr2);
            if(waitpid(childPid, &status,0) != childPid){
                perror("wait");
                exit(1);
            }
            pr_exit(status);
            break;
    }
}