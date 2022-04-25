#include "perror_header.h"
//Три sshd подряд

void pr_exit(int status){
    if (WIFEXITED(status)){
        printf("Нормальное завершение, код выхода = %d\n", WEXITSTATUS(status));
    }else if (WIFSIGNALED(status)){
        printf("Аварийное завершение, номер сигнала = %d\n", WTERMSIG(status));
    }else if (WIFSTOPPED(status)){
        printf("Дочерний процесс остановлен, номер сигнала = %d\n", WSTOPSIG(status));
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
            printf("This is child, childPid - %d\n", childPid);
            printf("child - %ld\n", (long)getpid());
            break;
        default:
            printf("This is parent\n");
            printf("parent - %ld\n", (long)getpid());
            sleep(5);
            printf("%d\n", childPid);
            if(waitpid(childPid,&status,0) != childPid){
                perror("wait");
                exit(1);
            }
            pr_exit(status);
            sleep(10);
            break;
    }

    // fork();
    // sleep(2);
    // fork();
    // sleep(2);
    // fork();
    // printf("Here\n");
    // sleep(5);

}