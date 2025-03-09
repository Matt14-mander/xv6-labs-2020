#include "kernel/types.h"
#include "user/user.h"
#include "stddef.h"

#define RD 0 //pipe的read端
#define WR 1 //pipe的write端

int main(int argc, char *argv[]){
    int ptoc_fd[2], ctop_fd[2];
    pipe(ptoc_fd);
    pipe(ctop_fd);
    char buf[8];
    int pid = fork(); // call mutiple times if fork() in if()!
    int exit_status = 0;

    if (pid < 0){
        fprintf(2, "pid error!\n");
        close(ptoc_fd[RD]);
        close(ptoc_fd[WR]);
        close(ctop_fd[RD]);
        close(ctop_fd[WR]);
        exit(1);
    }else if (pid == 0){
        // child process
        close(ptoc_fd[WR]);
        close(ctop_fd[RD]);

        if (read(ptoc_fd[RD], buf, 4) != 4){
            fprintf(2, "child read() error!\n");
            exit_status = 1;
        } else{
            // printf("%d: received %s\n", getpid(), buf);
            fprintf(1, "%d: received ping\n", getpid());
        }
        
        if (write(ctop_fd[1], "pong", strlen("pong")) != strlen("pong")){
            fprintf(2, "child write() error!\n");
            exit_status = 1;
        }

        close(ptoc_fd[RD]);
        close(ctop_fd[WR]);

        exit(exit_status);
    }else{
        // parent process
        close(ptoc_fd[RD]);
        close(ctop_fd[WR]);

        if (write(ptoc_fd[1], "ping", strlen("ping")) != strlen("ping")){
            fprintf(2, "parent write() error!\n");
            exit_status = 1;
        }

        wait(NULL);
        if (read(ctop_fd[0], buf, 4) != 4){
            fprintf(2, "parent read() error!\n");
            exit_status = 1;
        } else{
            // printf("%d: received %s\n", getpid(), buf);
            fprintf(1, "%d: received pong\n", getpid());
        }

        close(ptoc_fd[WR]);
        close(ctop_fd[RD]);
        
        exit(exit_status);
    }
}