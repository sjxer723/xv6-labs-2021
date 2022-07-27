#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



void primes(int p[])
{
    int prime = 0; 
    int n = 0;

    close(p[1]);
    if(read(p[0], &prime, 4) != 4){
        fprintf(2, "Fail to read primes from pipe %d\n", p[0]);
        exit(0);
    }
    printf("prime %d\n", prime);
    if(read(p[0], &n, 4) == 4) {
        int new_p[2];
            
        if(pipe(new_p) < 0){
            fprintf(2, "fail to create pipe\n");
            exit(0);
        }

        if(fork() == 0) {
            primes(new_p);    
        } else{
            close(new_p[0]);

            if(n % prime)
            {
                write(new_p[1], &n, 4);
            }
            while(read(p[0], &n, 4) == 4){
                if(n%prime){
                    write(new_p[1], &n, 4);
                }
            }
            close(new_p[1]);
            close(p[0]);
            wait(0);
        }
    }
    exit(0);
}

int main()
{
    int p[2];

    if(pipe(p) < 0){
        fprintf(2, "fail to create pipe\n");
        exit(0);
    }
    
    if(!fork()) {
        primes(p);
    } else {
        close(p[0]); // close the read descriptor
        for(int i = 2; i <= 35; i++)
        {
            if(write(p[1], &i, 4)!= 4)
            {
                fprintf(2, "fail to write number %d into descriptor %d\n", i, p[1]);
                exit(0);
            }
        }
        close(p[1]); // close the write descriptor
        wait(0);
    }

    exit(0);
    return 0;
}