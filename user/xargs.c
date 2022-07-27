#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(2, "usage: xargs command\n");
        exit(0);
    }

    char *_argv[MAXARG]; // store the arguments of xargs
    char buf[1024];
    char c = 0;

    for(int i=1; i <argc;i++) _argv[i-1] = argv[i];  // first store the pre-arguments 
    while(1)
    {
        int buf_end = 0, arg_start = 0;
        int argv_cnt = argc - 1;

        while (1)   // read one line 
        {
            if (!read(0, &c, 1)) exit(0);
            if (c == ' ' || c == '\n')
            {
                buf[buf_end++] = 0;
                _argv[argv_cnt++] = &buf[arg_start];
                arg_start = buf_end; 
                if (c == '\n') break;
            } 
            else buf[buf_end++] = c;
        }
        _argv[argv_cnt] = 0; // the arguments should be terminated as 0
        
        if (fork() == 0) exec(_argv[0], _argv);
        else wait(0);
    }
    exit(0);
}
