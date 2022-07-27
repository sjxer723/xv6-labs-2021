#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int pipe1[2];
    int pipe2[2];

    if(pipe(pipe1) < 0){
        printf("create pipe1 failed\n");
        exit(0);
    }
    if(pipe(pipe2) < 0){
        printf("create pipe2 failed\n");
        exit(0);
    }

    if(!fork()) {
        char send_buf[] = {1};
        char recv_buf[1];

        if(read(pipe2[0], recv_buf, 1)){
            printf("%d: received ping\n", getpid());
        }
        write(pipe1[1], send_buf, 1);
        
        exit(0);
    } else{
        char send_buf[] = {1};
        char recv_buf[1];

        write(pipe2[1], send_buf, 1);
        if(read(pipe1[0], recv_buf, 1)){
            printf("%d: received pong\n", getpid());
        }
    }
    exit(0);
    
}