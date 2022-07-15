#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int bytes[2];
    
    if(pipe(bytes) < 0){
      printf("pipe() failed\n");
      exit(0);
    }
    if(!fork()) {
        char send_buf[] = {1};
        char recv_buf[1];

        write(bytes[1], send_buf, 1);
        if(read(bytes[0], recv_buf, 1)){
            sleep(1);
            printf("%d: received ping\n", getpid());
        }
    } else{
        char send_buf[] = {1};
        char recv_buf[1];

        write(bytes[0], send_buf, 1);
        if(read(bytes[1], recv_buf, 1)){
            printf("%d: received pong\n", getpid());
        }
    }
    exit(0);
    
}