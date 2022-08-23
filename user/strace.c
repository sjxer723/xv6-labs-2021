#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define TRACE_MASK 2147483647

int
main(int argc, char *argv[])
{
  int i;
  char *nargv[MAXARG];

  if (trace(TRACE_MASK) < 0) {
    fprintf(2, "%s: trace failed\n", argv[0]);
    exit(1);
  }
  
  for(i = 1; i < argc && i < MAXARG; i++){
    nargv[i-1] = argv[i];
  }
  exec(nargv[0], nargv);
  exit(0);
}
