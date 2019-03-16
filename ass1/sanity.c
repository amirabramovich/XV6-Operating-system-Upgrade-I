#include "types.h"
#include "stat.h"
#include "user.h"


void
test2(void){
    uint pid;
    printf(1, "begin test2\n");
    policy(2);
    pid = fork();
    switch (pid)
    {
        case 0:
            sleep(20);
            priority(0);
            for(;;)
                printf(1,".");
            printf(1,"\nchild done\n");
            break;
        default:
            for(;;)
            printf(1,"\ni am not starving!\n");
            printf(1, "parent done\n");
            printf(1, "end of test2\n");
    }
}
int
main(int argc, char *argv[])
{
    uint pid, pid2;
    int first_status;
    int second_status;
    int third_status;
    int status;
    struct perf performance;
    printf(1, "begin test1\n");
    pid = fork(); // the child pid is pid
    switch (pid)
    {
        case 0: //child
            pid2 = fork();
            switch (pid2)
            {
                case 0: //child
                    sleep(10);
                    printf(1, "grandson done\n");
                    break;
            
                default:
                    first_status = detach(pid2); // status = 0
                    second_status = detach(pid2); // status = -1, because this process has already
                    // detached this child, and it doesn’t have
                    // this child anymore.
                    third_status = detach(77); // status = -1, because this process doesn’t
                    // have a child with this pid.
                    printf(2, "first_status is %d , second_status is %d , third_status is %d\n",
                    first_status,second_status,third_status );
                    printf(1, "child done\n");
            }
            break;
        default:
        wait_stat(&status, &performance);
        printf(2, "status is %d , ctime is %d, ttime is %d\nstime is %d, retime is %d, rutime is %d\n",
        status, performance.ctime,performance.ttime,
        performance.stime,performance.retime,performance.rutime );
        sleep(20);
        printf(1, "parent done\n");
        printf(1, "end of test1\n");
        test2();
    }
  exit(0);
}

