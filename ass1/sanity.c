#include "types.h"
#include "stat.h"
#include "user.h"

int
fibonacci(int num){
    if (num <= 1) 
      return num; 
   return fibonacci(num - 1) + fibonacci(num - 2);
}

void
test1(void){
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
                    exit(33);
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
                    exit(13);
            }
            exit(0);
            break;
        default:
        wait_stat(&status, &performance);
        printf(2, "status is %d , ctime is %d, ttime is %d\nstime is %d, retime is %d, rutime is %d\n",
        status, performance.ctime,performance.ttime,
        performance.stime,performance.retime,performance.rutime );
        sleep(20);
        printf(1, "parent done\n");
        printf(1, "end of test1\n");
    }
}

void
test2(void){
    uint pid;
    printf(1, "begin test2\n");
    policy(3);
    pid = fork();
    switch (pid)
    {
        case 0:
            priority(0);
            for(int i=0;i<500;++i)
                printf(1,".");
            printf(1,"\nchild done\n");
            exit(0);
            break;
        default:
            priority(10);
            for(int i=0;i<5;++i)
                printf(1,"\ni am not starving!\n");
            wait(0);
            printf(1, "parent done\n");
            printf(1, "end of test2\n");
    }
}

//Returns the performance of a proccess which runs fibbonaci(num)
struct perf
run_fib(int num){
    uint pid;
    int fib;
    int status;
    struct perf performance;
    pid = fork();
    switch (pid)
    {
        case 0:
            sleep(1);
            fib = fibonacci(num);
            exit(fib);
            break;
        default:
            wait_stat(&status, &performance);
            return performance;
    }
    
}

//Runs fibbonaci "n" times on each policy and prints performances
void 
test3(int n){
    struct perf performance;
    const int fib_num = 30;
    printf(1, "begin test3\n");
    printf(1, "policy|ctime|ttime|stime|retime|rutime\n");
    for(int j=0;j<n;++j)
        for(int i=1;i<=3;++i){
            policy(i);
            performance = run_fib(fib_num);
            printf(2, "    %d | %d | %d | %d   | %d    | %d\n",
            i,performance.ctime,performance.ttime,
            performance.stime,performance.retime,performance.rutime );
        }
    printf(1, "done test3\n");
}

int
main(int argc, char *argv[]){
    test1();
    test2();
    test3(3);
    exit(0);
}

