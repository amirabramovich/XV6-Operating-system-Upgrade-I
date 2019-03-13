#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    uint pid;
    int first_status;
    int second_status;
    int third_status;
    pid = fork(); // the child pid is pid
    if(pid > 0) {
        first_status = detach(pid); // status = 0
        second_status = detach(pid); // status = -1, because this process has already
        // detached this child, and it doesn’t have
        // this child anymore.
        third_status = detach(77); // status = -1, because this process doesn’t
        // have a child with this pid.
        printf(2, "first_status is %d , second_status is %d , third_status is %d\n",
        first_status,second_status,third_status );
    }
  exit(0);
}

