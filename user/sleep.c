#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int n = 0;

    if(argc <= 1) 
    {
        printf("usage: sleep pattern [time ]\n");
        exit(0);
    }
    n = atoi(argv[1]);
    sleep(n);
    exit(0);
}